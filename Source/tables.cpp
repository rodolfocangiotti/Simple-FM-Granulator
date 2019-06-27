#include <cmath>
#include "tables.h"

FunctionTable initSine(TableSize s) {
  FunctionTable t(s + 1, 0.0);  // Add guard point...
  for (int i = 0; i < s; i++) {
    double normPhase = static_cast<double>(i) / static_cast<double>(s);
    t[i] = sin(2.0 * M_PI * normPhase);
  }
  return t;
}



FunctionTable initBell(TableSize s) { // Gaussian bell...
  FunctionTable t(s + 2, 0.0);  // TODO Check if a single guard point is okay!
  for (int i = 0; i < s; i++) {
    double normPhase = static_cast<double>(i) / static_cast<double>(s);
    t[i] = (1.0 - cos(2.0 * M_PI * normPhase)) * 0.5;
  }
  return t;
}

FunctionTable initTriangle(TableSize s) {
  FunctionTable t(s + 2, 0.0);
  TableSize half = static_cast<TableSize>(s / 2);
  double incr = 1.0 / static_cast<double>(half);
  for (int i = 0; i < half ; i++) {
    t[i] = i * incr;
    t[i + half] = 1.0 - i * incr;
  }
  return t;
}

FunctionTable initTrapezoid(TableSize s) {
  FunctionTable t(s + 2, 0.0);
  TableSize quarter = static_cast<TableSize>(s / 4);
  double incr = 1.0 / static_cast<double>(quarter);
  for (int i = 0; i < quarter; i++) {
    t[i] = i * incr;
    t[i + quarter * 3] = 1.0 - i * incr;
  }
  for (int i = quarter; i < quarter * 3; i++) {
    t[i] = 1.0;
  }
  return t;
}

FunctionTable initSawtooth(TableSize s) {
  FunctionTable t(s + 2, 0.0);
  double incr = 1.0 / static_cast<double>(s);
  for (int i = 0; i < s; i++) {
    t[i] = 1.0 - i * incr;
  }
  return t;
}

FunctionTable initRectangle(TableSize s) {
  FunctionTable t(s + 2, 1.0);
  return t;
}

FunctionTable initCosineQuarter(TableSize s) {
  FunctionTable t(s + 1, 1.0);
  for (int i = 0; i < s; i++) {
    double normPhase = static_cast<double>(i) / static_cast<double>(s);
    t[i] = cos(0.5 * M_PI * normPhase);
  }
  return t;
}
