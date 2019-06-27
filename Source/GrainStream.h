#pragma once

#include <vector>
#include "Grain.h"
#include "ioformats.h"
#include "tables.h"
#include "types.h"

class GrainStream {
public:
  GrainStream();
  ~GrainStream();
  // ********************
  void setSampleRate(const SampleRate sr);
  void setMinimumTimeDelta(const GrainTimeDelta td);
  void setMaximumTimeDelta(const GrainTimeDelta td);
  void setMinimumDuration(const GrainDuration d);
  void setMaximumDuration(const GrainDuration d);
  void setMinimumModulationFrequency(const GrainFrequency f);
  void setMaximumModulationFrequency(const GrainFrequency f);
  void setMinimumModulationAmplitude(const GrainAmplitude a);
  void setMaximumModulationAmplitude(const GrainAmplitude a);
  void setMinimumMainFrequency(const GrainFrequency f);
  void setMaximumMainFrequency(const GrainFrequency f);
  void setMinimumMainAmplitude(const GrainAmplitude a);
  void setMaximumMainAmplitude(const GrainAmplitude a);
  void setModulationEnvelopeFunction(const EnvelopeID id);
  void setMainEnvelopeFunction(const EnvelopeID id);
  void setOscillatorWavetable(const WaveformID id);
  void setMinimumPan(const GrainPan p);
  void setMaximumPan(const GrainPan pr);
  // ********************
  StereoOutput process();
private:
  typedef std::vector<Grain> InstanceManager;
  // ********************
  const FunctionTable* getPointerToTable(const EnvelopeID id);
  const FunctionTable* getPointerToTable(const WaveformID id);
  void generateInstanceTimeDelta();
  void instanciateGrain();
  // ********************
  InstanceManager grains;
  // ********************
  Status status;
  GrainTimeDelta minDeT, maxDeT;
  GrainDuration minDur, maxDur;
  GrainFrequency minModFreq, maxModFreq;
  GrainAmplitude minModAmp, maxModAmp;
  GrainFrequency minMainFreq, maxMainFreq;
  GrainAmplitude minMainAmp, maxMainAmp;
  GrainPan minPan, maxPan;
  EnvelopeID mainEnvID;
  EnvelopeID modEnvID;
  WaveformID waveID;
  FunctionTable sine;
  FunctionTable bell;
  FunctionTable triangle;
  FunctionTable trapezoid;
  FunctionTable sawtooth;
  FunctionTable rectangle;
  FunctionTable cosineQuarter;
  DiscreteTime t, T;
  SampleRate sampRate;
};
