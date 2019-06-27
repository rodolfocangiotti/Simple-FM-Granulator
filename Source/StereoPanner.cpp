#include <cassert>
#include <iostream>
#include "StereoPanner.h"
#include "dsputils.h"

StereoPanner::StereoPanner():
  panVal(0.0),
  funcTab(nullptr) {
#if defined(DEBUG) && VERBOSENESS > 2
  std::cout << "Constructing StereoPanner class..." << '\n';
#endif
}

StereoPanner::~StereoPanner() {
#if defined(DEBUG) && VERBOSENESS > 2
  std::cout << "Destructing StereoPanner class..." << '\n';
#endif
}

void StereoPanner::setPan(const Pan p) {
  panVal = p;
  if (panVal > 1.0) {
    panVal = 1.0;
  } else if (panVal < 0.0) {
    panVal = 0.0;
  }
}

void StereoPanner::pointPanningFunction(const FunctionTable* ft) {
  funcTab = ft;
}

StereoOutput StereoPanner::process(const Sample s) {
  double i = panVal * (funcTab->size() - 2);
  int iInt = static_cast<int>(i);
  double iFrac = i - iInt;

  double j = (1.0 - panVal) * (funcTab->size() - 2);
  int jInt = static_cast<int>(j);
  double jFrac = j - jInt;

  StereoOutput out;
  out.leftSample = s * computeLinearInterp(funcTab->at(iInt), funcTab->at(iInt + 1), iFrac);
  out.rightSample = s * computeLinearInterp(funcTab->at(jInt), funcTab->at(jInt + 1), jFrac);
  return out;
}
