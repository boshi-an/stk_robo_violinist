/***************************************************/
/*! \file main.cpp
    \brief STK bowed string simulator using MyBowed.
*/
/***************************************************/

#include "MyBowed.h"
#include "FileWvOut.h"
#include "SKINImsg.h"
#include <iostream>

using namespace stk;

int main()
{
  const StkFloat SAMPLE_RATE = 44100.0;
  Stk::setSampleRate(SAMPLE_RATE);

  MyBowed bowed(20.0);
  bowed.setFrequency(196.0);
  bowed.controlChange(__SK_BowPosition_, 32.0);
  bowed.controlChange(__SK_BowPressure_, 64.0);
  bowed.startBowing(0.5, 0.1);

  FileWvOut output;
  output.openFile("bowed_output.wav", 1, FileWrite::FILE_WAV, Stk::STK_SINT16);

  for (int i = 0; i < 88200; ++i) output.tick(bowed.tick());
  bowed.stopBowing(0.01);
  for (int i = 0; i < 4410; ++i) output.tick(bowed.tick());

  std::cout << "Wrote bowed_output.wav\n";
  return 0;
}
