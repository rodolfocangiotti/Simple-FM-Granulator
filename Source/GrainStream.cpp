#include <cassert>
#include <iostream>
#include "GrainStream.h"
#include "commons.h"
#include "dsputils.h"

GrainStream::GrainStream():
  grains(),
  status(OFF),
  minDeT(0.0), maxDeT(0.0),
  minDur(0.0), maxDur(0.0),
  minModFreq(0.0), maxModFreq(0.0),
  minModAmp(0.0), maxModAmp(0.0),
  minMainFreq(0.0), maxMainFreq(0.0),
  minMainAmp(0.0), maxMainAmp(0.0),
  minPan(0.0), maxPan(0.0),
  mainEnvID(BELL_ENVELOPE), modEnvID(BELL_ENVELOPE), waveID(SINE_WAVE),
  sine(initSine(4096)), bell(initBell(4096)), triangle(initTriangle(4096)), trapezoid(initTrapezoid(4096)), sawtooth(initSawtooth(4096)),
  rectangle(initRectangle(4)),
  cosineQuarter(initCosineQuarter(1024)),
  t(0), T(0),
  sampRate(0) {
#if defined(DEBUG) && VERBOSENESS > 2
  std::cout << "Constructing GrainStream class..." << '\n';
#endif
  grains.reserve(MAX_INSTANCES);
  initRandomSeed();
}

GrainStream::~GrainStream() {
#if defined(DEBUG) && VERBOSENESS > 2
  std::cout << "Destructing GrainStream class..." << '\n';
#endif
}

void GrainStream::setSampleRate(const SampleRate sr) {
  assert(sr > 0);
  sampRate = sr;
}

void GrainStream::setMinimumTimeDelta(const GrainTimeDelta td) {
  minDeT = td;
}

void GrainStream::setMaximumTimeDelta(const GrainTimeDelta td) {
  maxDeT = td;
}

void GrainStream::setMinimumDuration(const GrainDuration d) {
  minDur = d;
}

void GrainStream::setMaximumDuration(const GrainDuration d) {
  maxDur = d;
}

void GrainStream::setMinimumModulationFrequency(const GrainFrequency f) {
  minModFreq = f;
}

void GrainStream::setMaximumModulationFrequency(const GrainFrequency f) {
  maxModFreq = f;
}

void GrainStream::setMinimumModulationAmplitude(const GrainAmplitude a) {
  minModAmp = a;
}

void GrainStream::setMaximumModulationAmplitude(const GrainAmplitude a) {
  maxModAmp = a;
}

void GrainStream::setMinimumMainFrequency(const GrainFrequency f) {
  minMainFreq = f;
}

void GrainStream::setMaximumMainFrequency(const GrainFrequency f) {
  maxMainFreq = f;
}

void GrainStream::setMinimumMainAmplitude(const GrainAmplitude a) {
  maxMainAmp = a;
}

void GrainStream::setMaximumMainAmplitude(const GrainAmplitude a) {
  minMainAmp = a;
}

void GrainStream::setMinimumPan(const GrainPan p) {
  minPan = p;
}

void GrainStream::setMaximumPan(const GrainPan p) {
  maxPan = p;
}

void GrainStream::setModulationEnvelopeFunction(const EnvelopeID id) {
  modEnvID = id;
}

void GrainStream::setMainEnvelopeFunction(const EnvelopeID id) {
  mainEnvID = id;
}

void GrainStream::setOscillatorWavetable(const WaveformID id) {
  waveID = id;
}

StereoOutput GrainStream::process() {
  if (T - t <= 0) {
    generateInstanceTimeDelta();
    instanciateGrain();
  }

  StereoOutput outStream;
  outStream.leftSample = 0.0;
  outStream.rightSample = 0.0;
  if (!(grains.empty())) {
    for (InstanceManager::iterator i = grains.begin(); i != grains.end(); i) {
      if (i->isProcessing()) {
        StereoOutput grain = i->process();
        outStream.leftSample += grain.leftSample;
        outStream.rightSample += grain.rightSample;
        i++;
      } else {
        grains.erase(i);
      }
    }
  }

  t++;
  return outStream;
}

const FunctionTable* GrainStream::getPointerToTable(const EnvelopeID id) {
  switch (id) {
  case BELL_ENVELOPE:
    return &bell;
  case TRIANGLE_ENVELOPE:
    return &triangle;
  case TRAPEZOID_ENVELOPE:
    return &trapezoid;
  case SAWTOOTH_ENVELOPE:
    return &sawtooth;
  case RECTANGLE_ENVELOPE:
    return &rectangle;
  default:
    return nullptr;
  }
}

const FunctionTable* GrainStream::getPointerToTable(const WaveformID id) {
  switch (id) {
  case SINE_WAVE:
    return &sine;
  default:
    return nullptr;
  }
}

void GrainStream::generateInstanceTimeDelta() {
  GrainTimeDelta newDeT = getRandomInRange<GrainTimeDelta>(minDeT, maxDeT);
  t = 0;
  T = static_cast<DiscreteTime>(newDeT * sampRate);
}

void GrainStream::instanciateGrain() {
  if (grains.size() < MAX_INSTANCES) {
    Grain newGrain;

    GrainDuration newDur = getRandomInRange<GrainDuration>(minDur, maxDur);
    GrainFrequency newModFreq = getRandomInRange<GrainFrequency>(minModFreq, maxModFreq);
    GrainAmplitude newModAmp = getRandomInRange<GrainAmplitude>(minModAmp, maxModAmp);
    GrainFrequency newMainFreq = getRandomInRange<GrainFrequency>(minMainFreq, maxMainFreq);
    GrainAmplitude newMainAmp = getRandomInRange<GrainAmplitude>(minMainAmp, maxMainAmp);
    GrainPan newPan = getRandomInRange(minPan, maxPan);
    EnvelopeID newModEnvID = modEnvID == RANDOM_ENVELOPE ? getRandomInRange<EnvelopeID>(BELL_ENVELOPE, SAWTOOTH_ENVELOPE) : modEnvID;
    EnvelopeID newMainEnvID = mainEnvID == RANDOM_ENVELOPE ? getRandomInRange<EnvelopeID>(BELL_ENVELOPE, SAWTOOTH_ENVELOPE) : mainEnvID;
    WaveformID newWaveID = waveID;

    newGrain.setSampleRate(sampRate);
    newGrain.setDuration(newDur);
    newGrain.setModulationFrequency(newModFreq);
    newGrain.setModulationAmplitude(newModAmp);
    newGrain.setMainFrequency(newMainFreq);
    newGrain.setMainAmplitude(newMainAmp);
    newGrain.setModulationEnvelopeFunction(getPointerToTable(newModEnvID));
    newGrain.setMainEnvelopeFunction(getPointerToTable(newMainEnvID));
    newGrain.setOscillatorWavetable(getPointerToTable(newWaveID));
    newGrain.setPan(newPan);
    newGrain.setPanningFunction(&cosineQuarter);
    grains.push_back(newGrain);
  }
}
