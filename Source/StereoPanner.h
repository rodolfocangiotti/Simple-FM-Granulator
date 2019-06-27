#ifndef STEREO_PANNER_H
#define STEREO_PANNER_H

#include "ioformats.h"
#include "tables.h"
#include "types.h"

class StereoPanner {
public:
  typedef double Pan;
  StereoPanner();
  ~StereoPanner();
  // ********************
  void setPan(Pan p);
  void pointPanningFunction(const FunctionTable* ft);
  // ********************
  StereoOutput process(const Sample i);
private:
  Pan panVal;
  const FunctionTable* funcTab;
};

#endif
