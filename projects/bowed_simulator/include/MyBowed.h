#ifndef STK_MYBOWED_H
#define STK_MYBOWED_H

#include "Bowed.h"
#include "BiQuad.h"
#include "NRev.h"

namespace stk {

/***************************************************/
/*! \class MyBowed
    \brief Custom bowed string class extending STK Bowed.

    This class inherits from the STK Bowed class and adds:
    - Multi-band resonance filtering with realistic violin body modes
    - Professional NRev reverb for realistic acoustic space
    - Enhanced control over bow parameters and resonance

    Control Changes:
    - 91: Reverb T60 (decay time) - 0.5 to 3.0 seconds
    - 92: Reverb mix level - 0.0 (dry) to 1.0 (wet)

    by Perry R. Cook and Gary P. Scavone, 1995--2023.
    Extended for realistic violin modeling by Boshi An, 2025.
*/
/***************************************************/

class MyBowed : public Bowed
{
public:
  // Control Change Numbers specific to MyBowed
  //  - MB_ReverbT60: Reverb T60 (decay time)
  //  - MB_ReverbMix: Reverb wet/dry mix
  static constexpr int MB_ReverbT60 = 91;
  static constexpr int MB_ReverbMix = 92;

  //! Constructor with multi-band resonance modeling
  MyBowed(StkFloat lowestFrequency = 20.0);

  //! Class destructor
  ~MyBowed( void );

  //! Enhanced tick method with realistic resonance modeling
  StkFloat tick( unsigned int channel = 0 );

  //! Custom control change with enhanced parameter mapping
  void controlChange(int number, StkFloat value);

  void setSampleRate(StkFloat sampleRate);

private:
  //! Apply realistic violin body resonance
  StkFloat applyViolinResonance(StkFloat input);

  //! Setup resonance filters for realistic violin body modeling
  void setupResonanceFilters();

  // Multi-band resonance filters for realistic violin body modeling
  BiQuad lowResonanceFilter_;   // A0 mode (280 Hz) - main air resonance
  BiQuad midResonanceFilter_;   // B1+ mode (480 Hz) - first wood resonance
  BiQuad highResonanceFilter_;  // CBR mode (1200 Hz) - corpus bending resonance
  
  // Professional reverb for realistic acoustic space
  NRev violinReverb_;           // CCRMA's NRev reverberator (1.2 second T60)
  StkFloat reverbMix_;          // Reverb mix level (0.0 = dry, 1.0 = wet)
};

} // stk namespace

#endif
