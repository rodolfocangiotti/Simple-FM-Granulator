#pragma once

#include "types.h"

Sample computeLinearInterp(Sample x0, Sample x1, double f);

void initRandomSeed();

template <typename T>
T getRandomInRange(T m, T n);
