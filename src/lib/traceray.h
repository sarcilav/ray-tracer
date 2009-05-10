#ifndef traceray_h
#define traceray_h

#include "primitives.h"

ColorFloat TraceRay(int ignoreNum, Ray &ray, Primitive *primitives, int numPrimitives, LightSource *lightSources, int numLightSources, int depth);

#endif
