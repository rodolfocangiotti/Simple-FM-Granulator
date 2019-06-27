#pragma once

#include "types.h"

struct Mono {
  Sample sample;
};

struct Stereo {
  Sample leftSample;
  Sample rightSample;
};

typedef Mono MonoInput;
typedef Mono MonoOutput;
typedef Stereo StereoInput;
typedef Stereo StereoOutput;
