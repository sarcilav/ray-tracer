#ifndef ray_h
#define ray_h

#include "primitives.h"

struct Ray
{
  Vector origin, direction;
};

struct TraceResult
{
  bool hit;
  float distance;
};
#endif
