#include <cassert>
#include <cmath>
#include <iostream>
#include "Oscillator.h"
#include "dsputils.h"


Oscillator::Oscillator():
  freq(0.0),
  phase(0.0),
  table(nullptr),
  sampRate(0) {
#if defined(DEBUG) && VERBOSENESS > 2
  std::cout << "Constructing Oscillator class..." << '\n';
#endif
}

Oscillator::~Oscillator() {
#if defined(DEBUG) && VERBOSENESS > 2
  std::cout << "Destructing Oscillator class.." << '\n';
#endif
}

void Oscillator::setSampleRate(const SampleRate sr) {
  assert(sr > 0);
  sampRate = sr;
}

void Oscillator::setFrequency(const Frequency f) {
  freq = f;
}

void Oscillator::pointWavetable(const FunctionTable* ft) {
  table = ft;
}

MonoOutput Oscillator::process() {
  assert(sampRate > 0);
  double i = phase * (table->size() - 1); // XXX Tables have always a guard point...
  int iInt = static_cast<int>(i);
  double iFrac = i - iInt;
  MonoOutput out;
  out.sample = computeLinearInterp(table->at(iInt), table->at(iInt + 1), iFrac);
  phase += freq / static_cast<double>(sampRate);
  phase -= floor(phase);
  return out;
}
