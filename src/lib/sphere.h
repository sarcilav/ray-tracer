#ifndef sphere_h
#define sphere_h

#include "primitives.h"

struct SphereProperties
{
  Vector center;
  float radius;
};

TraceResult IntersectSphere(SphereProperties &sphere, Ray &ray);
Vector SphereNormal(SphereProperties &sphere, Vector &intersection);

#endif
