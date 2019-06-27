#pragma once

#include "ioformats.h"
#include "tables.h"
#include "types.h"

class Oscillator {
public:
  typedef double Frequency;
  typedef double Phase;
  Oscillator();
  ~Oscillator();
  // ********************
  void setSampleRate(const SampleRate sr);
  void setFrequency(const Frequency f);
  void pointWavetable(const FunctionTable* ft);
  // ********************
  MonoOutput process();
private:
  Frequency freq;
  Phase phase;
  const FunctionTable* table;
  SampleRate sampRate;
};
