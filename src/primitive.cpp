#include "lib/primitives.h"

void AssignPrimitiveType(Primitive &primitive, PrimitiveType type)
{
  switch(type)
    {
    case SPHERE_TYPE:
      primitive.type = SPHERE_TYPE;
      primitive.sphereProperties = new SphereProperties;
      break;
    case PLANE_TYPE:
      primitive.type = PLANE_TYPE;
      primitive.planeProperties = new PlaneProperties;
      break;
    case CYLINDER_TYPE:
      primitive.type = CYLINDER_TYPE;
      primitive.cylinderProperties = new CylinderProperties;
      break;
    case TRIANGLE_TYPE:
      primitive.type = TRIANGLE_TYPE;
      primitive.triangleProperties = new TriangleProperties;
      break;
    }
}

void ClearPrimitiveType(Primitive &primitive)
{
  switch(primitive.type)
    {
    case SPHERE_TYPE:
      delete primitive.sphereProperties;
      break;
    case PLANE_TYPE:
      delete primitive.planeProperties;
      break;
    case CYLINDER_TYPE:
      delete primitive.cylinderProperties;
      break;
    case TRIANGLE_TYPE:
      delete primitive.triangleProperties;
      break;
    }
}


