#ifndef cylinder_h
#define cylinder_h

#include "primitives.h"

enum Axis{X_INFINITE, Y_INFINITE, Z_INFINITE};

struct CylinderProperties
{
  Vector center;
  float radius;
  Axis axis;
};

TraceResult IntersectCylinder(CylinderProperties &cylinder, Ray &ray);
Vector CylinderNormal(CylinderProperties &cylinder, Vector &intersection);

#endif
