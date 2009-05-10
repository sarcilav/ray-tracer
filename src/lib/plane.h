#ifndef plane_h
#define plane_h

#include "primitives.h"

struct PlaneProperties
{
  Vector normal;
  float displacement;
};

TraceResult IntersectPlane(PlaneProperties &plane, Ray &ray);
inline Vector PlaneNormal(PlaneProperties &plane) { return plane.normal; }

#endif
