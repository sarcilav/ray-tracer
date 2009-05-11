#include "lib/primitives.h"

TraceResult IntersectTriangle(TriangleProperties &triangle, Ray &ray)
{

  TraceResult traceResult;
  float u, v;
  Vector edge1, edge2, tvec, pvec, qvec;
  float det, invDet;
    
  edge1 = VectorSub(*triangle.v2 , *triangle.v1);
  edge2 = VectorSub(*triangle.v3 , *triangle.v1);
  pvec = VectorCross(ray.direction, edge2);
    
  det = VectorDot(edge1, pvec);

  if(det > -.000001 && det < .000001)
    {
      traceResult.hit=false;
      return traceResult;
    }
  invDet = 1/det;

  tvec = VectorSub(ray.origin , *triangle.v1);

  u = VectorDot(tvec, pvec) * invDet;
  if(u < 0 || u > 1)
    {
      traceResult.hit=false;
      return traceResult;
    }

  qvec = VectorCross(tvec, edge1);

  v = VectorDot(ray.direction, qvec) * invDet;
  if(v < 0 || (u + v) > 1)
    {
      traceResult.hit=false;
      return traceResult;
    }
      
    
  traceResult.distance = VectorDot(edge2, qvec) * invDet;
  if(traceResult.distance < 0)
    {
      traceResult.hit=false;
      return traceResult;
    }
   
  traceResult.hit = true;
  return traceResult;
}

Vector TriangleNormal(TriangleProperties &triangle)
{
  Vector edge1 = VectorSub(*triangle.v2 , *triangle.v1), edge2 = VectorSub(*triangle.v3 , *triangle.v1);
  Vector normal = VectorCross(edge1, edge2); 
  VectorNormalize(normal);
  return normal;
}
