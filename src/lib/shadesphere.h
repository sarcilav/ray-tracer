#ifndef shadesphere_h
#define shadesphere_h

#include "reflections.h"

ColorFloat ShadeSphere(	Sphere &sphere, int currSphereNum,Ray &ray, float distance, Vector &lightLoc, Sphere *spheres, int numSpheres, int depth);

#endif
