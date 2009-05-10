#ifndef tracescene_h
#define tracescene_h

#include "primitives.h"

Vector* GenerateRayDirectionTable();

void TraceScene(Primitive *primitives, int numPrimitives, LightSource *lightSources, int numLightSources, unsigned int* buffer, Vector *directionTable);

#endif
