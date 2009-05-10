#ifndef triangle_h
#define triangle_h

#include "primitives.h"

struct TriangleProperties 
{
  Vector *v1, *v2, *v3; // vertices
};

TraceResult IntersectTriangle(TriangleProperties &triangle, Ray &ray);
Vector TriangleNormal(TriangleProperties &triangle);

#endif
