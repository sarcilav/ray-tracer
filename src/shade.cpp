
#include "lib/primitives.h"

inline Vector CalculateIntersection(Ray &ray, float distance)
{	
  Vector intersection;
  // intersection between the primitive and the ray 
  intersection.x = ray.origin.x + distance * ray.direction.x;
  intersection.y = ray.origin.y + distance * ray.direction.y;
  intersection.z = ray.origin.z + distance * ray.direction.z;
  return intersection;
}

inline float CalculateLightRay(Vector &lightLoc, Vector&intersection, Ray &rayToLight) 
{
  Vector lightDir = VectorSub(lightLoc, intersection);
  float distanceToLight = sqrt( (lightDir.x * lightDir.x) + (lightDir.y * lightDir.y) + (lightDir.z * lightDir.z) );//normal
  float lightDirMagnitudeReciprocal = 1 / distanceToLight;
  lightDir.x *= lightDirMagnitudeReciprocal;
  lightDir.y *= lightDirMagnitudeReciprocal;
  lightDir.z *= lightDirMagnitudeReciprocal;

  rayToLight.origin = intersection;
  rayToLight.direction = lightDir;
    
  return distanceToLight;
}

inline float CalculateLightingCoef(bool isShadowed, Vector &directionToLight, Vector &normal)
{
  if( isShadowed )
    // no light
    return 0;
  else
    { // how much light 
      float lightCoef = VectorDot(directionToLight, normal);
      if (lightCoef < 0 ) lightCoef = 0;
      return lightCoef;
    }
}

inline ColorFloat CalculateReflection(Ray &ray, Vector &intersection, Vector &normal, int currPrimitiveNum, Primitive *primitives, int numPrimitives, LightSource *lightSources, int numLightSources, int depth)
{
  // R = I - 2(N.I)*N
  Ray reflectedRay;
  float nDotI = 2*((normal.x * ray.direction.x) + (normal.y * ray.direction.y) + (normal.z * ray.direction.z)); 
  reflectedRay.direction.x = ray.direction.x - (nDotI * normal.x);					
  reflectedRay.direction.y = ray.direction.y - (nDotI * normal.y); 
  reflectedRay.direction.z = ray.direction.z - (nDotI * normal.z);
  reflectedRay.origin = intersection;
    
  return TraceRay(currPrimitiveNum, reflectedRay, primitives, numPrimitives, lightSources, numLightSources, depth + 1);
}

ColorFloat Shade(Primitive &primitive, int currPrimitiveNum, Ray &ray, float distance, LightSource *lightSources, int numLightSources, Primitive *primitives, int numPrimitives, int depth)
{
  ColorFloat returnColor;
  returnColor.r=0;
  returnColor.g=0;
  returnColor.b=0;
    
  Vector intersection = CalculateIntersection(ray,distance);
    
  Vector normal = CalculateNormal(primitive, intersection);
    
  //specular
  for(int i=0; i<numLightSources; i++)
    {
      Ray rayToLight;
      float distanceToLight = CalculateLightRay(lightSources[i].location, intersection, rayToLight); // sets rayToLight
      float lightCoef = CalculateLightingCoef(IsShadowed(currPrimitiveNum, rayToLight, distanceToLight, primitives, numPrimitives) , rayToLight.direction, normal); 
      returnColor.r += primitive.surface.baseColor.r * lightCoef * lightSources[i].color.r; // try checking first if lightCoef is 0... the check will probably be amortized over the 
      returnColor.g += primitive.surface.baseColor.g * lightCoef * lightSources[i].color.g; // cost of all these multiplications
      returnColor.b += primitive.surface.baseColor.b * lightCoef * lightSources[i].color.b; 
    }
    
  //reflective
  if(primitive.surface.reflectivity!=0)
    {
      ColorFloat reflectedColor = CalculateReflection(ray, intersection, normal, currPrimitiveNum, primitives, numPrimitives, lightSources, numLightSources, depth);
      returnColor.r +=  reflectedColor.r * primitive.surface.reflectivity; 
      returnColor.g +=  reflectedColor.g * primitive.surface.reflectivity; 
      returnColor.b +=  reflectedColor.b * primitive.surface.reflectivity;
    }
    
  return returnColor;
}
