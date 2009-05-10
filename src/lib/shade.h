#ifndef shade_h
#define shade_h

#include "primitives.h"

ColorFloat Shade(Primitive &primitive, int currPrimitiveNum,Ray &ray, float distance, LightSource *lightSources, int numLightSources, Primitive *primitives, int numPrimitives, int depth);

#endif
