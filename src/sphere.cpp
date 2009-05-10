#include "lib/primitives.h"

TraceResult IntersectSphere(SphereProperties &sphere, Ray &ray)
{
  TraceResult traceResult;
    
  Vector rayToSphereCenter = VectorSub( sphere.center, ray.origin);
  float lengthRTSC2 = VectorDot( rayToSphereCenter, rayToSphereCenter ); // lengthRTSC2 = length of the ray from the ray's origin to the sphere's center squared
      
  float closestApproach = VectorDot( rayToSphereCenter, ray.direction );
  if (closestApproach < 0 ) // behind the ray origin
    {
      traceResult.hit = false;
      return traceResult;
    }
    
  float halfCord2 = (sphere.radius * sphere.radius) - lengthRTSC2 + (closestApproach * closestApproach); 
  if(halfCord2 < 0) // no intersection
    {
      traceResult.hit = false;
      return traceResult;
    }
    
  traceResult.hit = true;
  traceResult.distance = closestApproach - sqrt(halfCord2);
  return traceResult;
}

Vector SphereNormal(SphereProperties &sphere, Vector &intersection)
{
  Vector normal;
  // the normal of the sphere at the point of interesction
  float oneOverRadius = 1/sphere.radius;
  normal.x = ( intersection.x - sphere.center.x ) * oneOverRadius; 
  normal.y = ( intersection.y - sphere.center.y ) * oneOverRadius;
  normal.z = ( intersection.z - sphere.center.z ) * oneOverRadius;  
  return normal;
}
