#ifndef isshadowed_h
#define isshadowed_h

#include "primitives.h"

bool IsShadowed(int currPrimitiveNum, Ray &rayToLight, float distanceToLight, Primitive *primitives, int numPrimitives);

#endif
