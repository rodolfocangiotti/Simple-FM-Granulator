#include <cassert>
#include <cmath>
#include <cstdlib>
#include "dsputils.h"

Sample computeLinearInterp(Sample x0, Sample x1, double f) {
  return x0 * (1.0 - f) + x1 * f;
}

void initRandomSeed() {
  srand(time(nullptr));
}

template <typename T>
T getRandomInRange(T m, T n) {
  //assert(m <= n);
  //m = m < 0 ? 0 : m;
  double normRand = static_cast<double>(rand()) / static_cast<double>(RAND_MAX);
  return static_cast<T>(normRand * (n - m) + m);
}

template double getRandomInRange<double>(double m, double n);
template EnvelopeID getRandomInRange<EnvelopeID>(EnvelopeID m, EnvelopeID n);

/*
 template short getRandomInRange<short>(short m, short n);
 template unsigned short getRandomInRange<unsigned short>(unsigned short m, unsigned short n);
 template int getRandomInRange<int>(int m, int n);
 template unsigned int getRandomInRange<unsigned int>(unsigned int m, unsigned int n);
 template long getRandomInRange<long>(long m, long n);
 template unsigned long getRandomInRange<unsigned long>(unsigned long m, unsigned long n);
 */
