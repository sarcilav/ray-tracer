#include "lib/primitives.h"

TraceResult IntersectCylinder(CylinderProperties &cylinder, Ray &ray)
{
  TraceResult traceResult;
  float a, b, c;
  switch(cylinder.axis)
    {
    case X_INFINITE:
      a = ray.direction.y * ray.direction.y + ray.direction.z * ray.direction.z;
                
      b = 2*(ray.direction.y * (ray.origin.y - cylinder.center.y) + 	ray.direction.z * (ray.origin.z - cylinder.center.z));
                        
      c = (ray.origin.y - cylinder.center.y) * (ray.origin.y - cylinder.center.y) + (ray.origin.z - cylinder.center.z) * (ray.origin.z - cylinder.center.z) - cylinder.radius * cylinder.radius;
      break;
    case Y_INFINITE:
      a = ray.direction.x * ray.direction.x + ray.direction.z * ray.direction.z;
                
      b = 2*(ray.direction.x * (ray.origin.x - cylinder.center.x) + 	ray.direction.z * (ray.origin.z - cylinder.center.z));

      c = (ray.origin.x - cylinder.center.x) * (ray.origin.x - cylinder.center.x) + (ray.origin.z - cylinder.center.z) * (ray.origin.z - cylinder.center.z) - cylinder.radius * cylinder.radius;
      break;
    case Z_INFINITE:
      a = ray.direction.x * ray.direction.x + ray.direction.y * ray.direction.y; 
                
      b = 2*(ray.direction.x * (ray.origin.x - cylinder.center.x) + ray.direction.y * (ray.origin.y - cylinder.center.y));
                        
      c = (ray.origin.x - cylinder.center.x) * (ray.origin.x - cylinder.center.x) + (ray.origin.y - cylinder.center.y) * (ray.origin.y - cylinder.center.y) - cylinder.radius * cylinder.radius;                    
      break;
    }    
                
  float discriminant = b*b - 4*a*c;
  if(discriminant<0)
    {
      traceResult.hit=false;
      return traceResult;
    }
    
  traceResult.distance = (-b - sqrt(discriminant)) / (2 * a);
  if(traceResult.distance<0)
    {
      traceResult.hit=false;
      return traceResult;
    }
  traceResult.hit = true;
  return traceResult;
}

Vector CylinderNormal(CylinderProperties &cylinder, Vector &intersection)
{
  Vector normal;
  float oneOverRadius = 1/cylinder.radius;
  switch(cylinder.axis)
    {
    case X_INFINITE:
      normal.x = 0;
      normal.y = ( intersection.y - cylinder.center.y ) * oneOverRadius; 
      normal.z = ( intersection.z - cylinder.center.z ) * oneOverRadius;  
      break;
    case Y_INFINITE:
      normal.x = ( intersection.x - cylinder.center.x ) * oneOverRadius; 
      normal.y = 0;
      normal.z = ( intersection.z - cylinder.center.z ) * oneOverRadius;  
      break;
    case Z_INFINITE:
      normal.x = ( intersection.x - cylinder.center.x ) * oneOverRadius; 
      normal.y = ( intersection.y - cylinder.center.y ) * oneOverRadius; 
      normal.z = 0;
    }
  return normal;
}



