#pragma once

#include <vector>

enum status {
  OFF,
  ON
};

enum waveformID {
  SINE_WAVE
};

enum envelopeID {
  BELL_ENVELOPE,
  TRIANGLE_ENVELOPE,
  TRAPEZOID_ENVELOPE,
  SAWTOOTH_ENVELOPE,
  RECTANGLE_ENVELOPE,
  RANDOM_ENVELOPE
};


typedef long DiscreteTime;


typedef uint32_t SampleRate;
typedef double Sample;


typedef std::vector<Sample> FunctionTable;
typedef uint64_t TableSize;


typedef double GrainAmplitude;
typedef double GrainFrequency;
typedef double GrainDuration;
typedef double GrainTimeDelta;
typedef double GrainPan;

typedef envelopeID EnvelopeID;
typedef waveformID WaveformID;

typedef status Status;
