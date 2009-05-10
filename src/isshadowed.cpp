#include "lib/primitives.h"

bool IsShadowed(int currPrimitiveNum, Ray &rayToLight, float distanceToLight, Primitive *primitives, int numPrimitives)
{  
  TraceResult traceResult;
  traceResult.hit=false;
  // check all spheres 
  for(int i=0; i<numPrimitives; i++)
    {
      if( i == currPrimitiveNum ) continue;//no auto
      
      switch(primitives[i].type)
        {
	case SPHERE_TYPE: 
	  traceResult = IntersectSphere(*primitives[i].sphereProperties, rayToLight);
	  break;
	case PLANE_TYPE:
	  traceResult = IntersectPlane(*primitives[i].planeProperties, rayToLight);
	  break;
	case CYLINDER_TYPE:
	  traceResult = IntersectCylinder(*primitives[i].cylinderProperties, rayToLight);
	  break;
	case TRIANGLE_TYPE:
	  traceResult = IntersectTriangle(*primitives[i].triangleProperties, rayToLight);
	  break;
	default:
	  continue; 
	  break;
        }
        
      if( traceResult.hit && (traceResult.distance < distanceToLight) )
	return true;
        
    }
    
  return false;
}
