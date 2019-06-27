#include <cassert>
#include <iostream>
#include "Grain.h"
#include "dsputils.h"

Grain::Grain():
  dur(0.0),
  modFreq(0.0), modAmp(0.0),
  mainFreq(0.0), mainAmp(0.0),
  modEnv(nullptr), mainEnv(nullptr),
  modOsc(), mainOsc(), panner(),
  t(0), T(0),
  sampRate(0) {
#if defined(DEBUG) && VERBOSENESS > 2
  std::cout << "Constructing Grain class..." << '\n';
#endif
}

Grain::~Grain() {
#if defined(DEBUG) && VERBOSENESS > 2
  std::cout << "Destructing Grain class..." << '\n';
#endif
}

void Grain::setSampleRate(const SampleRate sr) {
  assert(sr > 0);
  sampRate = sr;
  modOsc.setSampleRate(sr);
  mainOsc.setSampleRate(sr);
}

void Grain::setDuration(const GrainDuration d) {
  assert(d > 0.0);
  dur = d;
  T = static_cast<DiscreteTime>(d * sampRate);  // Duration in samples...
  //assert(T > 0);
  // XXX With randomly generated very low duration values, casting to an integer-derived data type can set T to zero...
  T = T > 0 ? T : 1;
}

void Grain::setModulationFrequency(const GrainFrequency f) {
  modFreq = f;
}

void Grain::setModulationAmplitude(const GrainAmplitude a) {
  modAmp = a;
}

void Grain::setMainFrequency(const GrainFrequency f) {
  mainFreq = f;
}

void Grain::setMainAmplitude(const GrainAmplitude a) {
  mainAmp = a;
}

void Grain::setModulationEnvelopeFunction(const FunctionTable* ft) {
  modEnv = ft;
}

void Grain::setMainEnvelopeFunction(const FunctionTable* ft) {
  mainEnv = ft;
}

void Grain::setOscillatorWavetable(const FunctionTable* ft) {
  mainOsc.pointWavetable(ft);
  modOsc.pointWavetable(ft);
}

void Grain::setPan(const GrainPan p) {
  pan = p;
}

void Grain::setPanningFunction(const FunctionTable* ft) {
  panner.pointPanningFunction(ft);
}

StereoOutput Grain::process() {
  assert(mainEnv != nullptr);
  assert(modEnv != nullptr);
  assert(T > 0); // XXX Considering the comment at line 36, yes, this assertion is almost useless...
  assert(t < T);

  double i = static_cast<double>(t) / static_cast<double>(T) * (modEnv->size() - 1);  // Do not consider guard point, then subtract it from table size...
  int iInt = static_cast<int>(i);
  double iFrac = i - iInt;
  Sample modEnvSamp = computeLinearInterp(modEnv->at(iInt), modEnv->at(iInt + 1), iFrac);

  modOsc.setFrequency(modFreq);
  MonoOutput modOscOut = modOsc.process();
  modOscOut.sample *= modEnvSamp * modAmp;

  double j = static_cast<double>(t) / static_cast<double>(T) * (mainEnv->size() - 1);
  int jInt = static_cast<int>(j);
  double jFrac = j - jInt;
  Sample mainEnvSamp = computeLinearInterp(mainEnv->at(jInt), mainEnv->at(jInt + 1), jFrac);

  mainOsc.setFrequency(mainFreq + modOscOut.sample);
  MonoOutput mainOscOut = mainOsc.process();
  mainOscOut.sample *= mainEnvSamp * mainAmp;

  panner.setPan(pan);
  StereoOutput pannerOut = panner.process(mainOscOut.sample);

  t++;
  return pannerOut;
}

bool Grain::isProcessing() const {
  return t < T ? true: false;
}
