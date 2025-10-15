/***************************************************/
/*! \file MyBowed.cpp
    \brief Implementation of MyBowed class - Enhanced bowed string with realistic violin resonance.

    by Boshi An, 2025.
*/
/***************************************************/

#include "MyBowed.h"
#include "SKINImsg.h"
#include <iostream>

using namespace stk;

MyBowed::MyBowed(StkFloat lowestFrequency) 
  : Bowed(lowestFrequency), violinReverb_(1.2), reverbMix_(0.3)
{
  setupResonanceFilters();
}

MyBowed::~MyBowed( void ) {}

StkFloat MyBowed::tick( unsigned int channel )
{
  StkFloat bowedOutput = Bowed::tick(channel);
  StkFloat resonanceOutput = applyViolinResonance(bowedOutput);
  StkFloat reverbOutput = violinReverb_.tick(resonanceOutput, channel);
  StkFloat dryMix = 1.0 - reverbMix_;
  StkFloat finalOutput = (dryMix * resonanceOutput) + (reverbMix_ * reverbOutput);
  lastFrame_[0] = finalOutput;
  return finalOutput;
}

void MyBowed::setSampleRate(StkFloat sampleRate)
{
  Stk::setSampleRate(sampleRate);
}

void MyBowed::controlChange( int number, StkFloat value )
{
  if ( number == __SK_BowPressure_ ) {
    StkFloat normalizedValue = value * ONE_OVER_128;
    bowDown_ = (normalizedValue > 0.0);
    bowTable_.setSlope(5.0 - (4.0 * normalizedValue));
  } else if ( number == MyBowed::MB_ReverbT60 ) {
    StkFloat t60 = 0.5 + (value * 0.02);
    violinReverb_.setT60(t60);
  } else if ( number == MyBowed::MB_ReverbMix ) {
    reverbMix_ = value * ONE_OVER_128;
  } else {
    Bowed::controlChange(number, value);
  }
}

StkFloat MyBowed::applyViolinResonance(StkFloat input)
{
  StkFloat output = input;
  StkFloat lowResonance = lowResonanceFilter_.tick(input);
  output += lowResonance * 0.4;
  StkFloat midResonance = midResonanceFilter_.tick(input);
  output += midResonance * 0.3;
  StkFloat highResonance = highResonanceFilter_.tick(input);
  output += highResonance * 0.2;
  return output;
}

void MyBowed::setupResonanceFilters()
{
  lowResonanceFilter_.setResonance(280.0, 0.95, true);
  midResonanceFilter_.setResonance(480.0, 0.90, true);
  highResonanceFilter_.setResonance(1200.0, 0.85, true);
}
