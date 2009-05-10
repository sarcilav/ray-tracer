#ifndef primitive_h
#define primitive_h

#include "primitives.h"

enum PrimitiveType {SPHERE_TYPE, PLANE_TYPE, CYLINDER_TYPE, TRIANGLE_TYPE};

struct Primitive
{
  Surface surface;
  PrimitiveType type;   
  PlaneProperties *planeProperties;
  SphereProperties *sphereProperties;
  CylinderProperties *cylinderProperties;
  TriangleProperties *triangleProperties;
};

void AssignPrimitiveType(Primitive &primitive, PrimitiveType type);
void ClearPrimitiveType(Primitive &primitive);
inline TraceResult IntersectPrimitive(Primitive &primitive, Ray &ray)
{
  switch(primitive.type)
    {
    case SPHERE_TYPE: 
      return IntersectSphere(*primitive.sphereProperties, ray);
    case PLANE_TYPE:
      return IntersectPlane(*primitive.planeProperties, ray);
    case CYLINDER_TYPE:
      return IntersectCylinder(*primitive.cylinderProperties, ray);
    case TRIANGLE_TYPE:
      return IntersectTriangle(*primitive.triangleProperties, ray);
    default: break;
    }
}

inline Vector CalculateNormal(Primitive &primitive, Vector &intersection)
{
  switch(primitive.type)
    {
    case SPHERE_TYPE:
      return SphereNormal(*primitive.sphereProperties, intersection);
    case PLANE_TYPE:
      return PlaneNormal(*primitive.planeProperties);
    case CYLINDER_TYPE:
      return CylinderNormal(*primitive.cylinderProperties, intersection);
    case TRIANGLE_TYPE:
      return TriangleNormal(*primitive.triangleProperties);
    default: break;
    }
}
#endif
