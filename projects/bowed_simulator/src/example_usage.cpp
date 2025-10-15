// Minimal quick start example for MyBowed
/***************************************************/
/*! \file example_usage.cpp
    \brief Minimal quick start using MyBowed to render 2 seconds to a WAV file.
*/
/***************************************************/

#include "MyBowed.h"
#include "FileWvOut.h"
#include "SKINImsg.h"
#include <iostream>

using namespace stk;

int main()
{
  try {
    Stk::setSampleRate(44100.0);
    MyBowed violin(20.0);
    violin.setFrequency(196.0);
    violin.controlChange(__SK_BowPosition_, 32.0);
    violin.controlChange(__SK_BowPressure_, 64.0);
    violin.controlChange(92, 40.0);
    violin.startBowing(0.5, 0.1);

    FileWvOut output;
    output.openFile("quick_start.wav", 1, FileWrite::FILE_WAV, Stk::STK_SINT16);
    for (int i = 0; i < 88200; i++) output.tick(violin.tick());
    violin.stopBowing(0.01);
    for (int i = 0; i < 4410; i++) output.tick(violin.tick());
    std::cout << "Wrote quick_start.wav" << std::endl;
  } catch (StkError &e) {
    std::cerr << "Error: " << e.getMessage() << '\n';
    return 1;
  }
  return 0;
}
