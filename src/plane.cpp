#include "lib/primitives.h"
TraceResult IntersectPlane(PlaneProperties &plane, Ray &ray)
{
  TraceResult traceResult;
  float t =-(plane.normal.x*ray.origin.x + plane.normal.y*ray.origin.y + plane.normal.z*ray.origin.z + plane.displacement) / 
    (plane.normal.x * ray.direction.x + plane.normal.y * ray.direction.y + plane.normal.z * ray.direction.z );
  if(t<0)
    {
      traceResult.hit=false;
      return traceResult;
    }
  traceResult.hit=true;
  traceResult.distance=t;
  return traceResult;
}
