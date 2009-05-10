#ifndef light_h
#define light_h

#include "primitives.h"

struct LightSource
{
  Vector location;
  ColorFloat color; // 0-1
};

#endif
