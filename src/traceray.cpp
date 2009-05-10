#include "lib/primitives.h"

ColorFloat TraceRay(int ignoreNum, Ray &ray, Primitive *primitives, int numPrimitives, LightSource *lightSources, int numLightSources, int depth)
{
  ColorFloat returnColor;
  if(depth>5) // prevent infinite reflection
    {
      returnColor.r=0;
      returnColor.g=0;
      returnColor.b=0;
      return returnColor;
    }
    
  float closestIntersectionDistance = 100000; // an impossibly large value
  int closestIntersectedPrimitiveNum = -1;
  TraceResult currResult;
    
  for(int currPrimitiveNum=0; currPrimitiveNum < numPrimitives; currPrimitiveNum++ ) // cycle through all of the spheres to find the closest interesction
    {
      if(currPrimitiveNum == ignoreNum) continue;
        
      currResult = IntersectPrimitive(primitives[currPrimitiveNum], ray);
        
      if(currResult.hit &&currResult.distance < closestIntersectionDistance)
	{
	  closestIntersectionDistance = currResult.distance;
	  closestIntersectedPrimitiveNum = currPrimitiveNum;
	}
    }
    
  if( closestIntersectedPrimitiveNum == -1) // nothing was intersected
    {
      returnColor.r=0;
      returnColor.g=0;
      returnColor.b=0;
    }
  else
    returnColor = Shade(primitives[closestIntersectedPrimitiveNum], closestIntersectedPrimitiveNum, ray, closestIntersectionDistance, lightSources, numLightSources, primitives,numPrimitives,depth);
  return returnColor;

}
