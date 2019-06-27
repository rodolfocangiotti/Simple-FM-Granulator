#pragma once

#include "Oscillator.h"
#include "StereoPanner.h"
#include "ioformats.h"
#include "tables.h"
#include "types.h"

class Grain {
public:
  Grain();
  ~Grain();
  // ********************
  void setSampleRate(const SampleRate sr);
  void setDuration(const GrainDuration d);
  void setModulationFrequency(const GrainFrequency f);
  void setModulationAmplitude(const GrainAmplitude a);
  void setMainFrequency(const GrainFrequency f);
  void setMainAmplitude(const GrainAmplitude a);
  void setModulationEnvelopeFunction(const FunctionTable* ft);
  void setMainEnvelopeFunction(const FunctionTable* ft);
  void setOscillatorWavetable(const FunctionTable* ft);
  void setPan(const GrainPan p);
  void setPanningFunction(const FunctionTable* ft);
  // ********************
  StereoOutput process();
  // ********************
  bool isProcessing() const;
private:
  GrainDuration dur;
  GrainFrequency modFreq;
  GrainAmplitude modAmp;
  GrainFrequency mainFreq;
  GrainAmplitude mainAmp;
  GrainPan pan;
  const FunctionTable* modEnv;
  const FunctionTable* mainEnv;
  // ********************
  Oscillator modOsc;
  Oscillator mainOsc;
  StereoPanner panner;
  // ********************
  DiscreteTime t, T;  // Current tau, grain life tau value...
  SampleRate sampRate;
};
