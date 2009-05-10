#include "lib/primitives.h"

void SetupScene(Primitive *primitives, int numPrimitives, Vector *vertices, int numVertices, LightSource *lightSources, int numLightSources)
{
  AssignPrimitiveType(primitives[0], PLANE_TYPE);
  primitives[0].planeProperties->displacement=150;

  AssignPrimitiveType(primitives[1], TRIANGLE_TYPE);
  primitives[1].triangleProperties->v1=&vertices[0];
  primitives[1].triangleProperties->v2=&vertices[1];
  primitives[1].triangleProperties->v3=&vertices[2];

  AssignPrimitiveType(primitives[2], TRIANGLE_TYPE);
  primitives[2].triangleProperties->v1=&vertices[0];
  primitives[2].triangleProperties->v2=&vertices[3];
  primitives[2].triangleProperties->v3=&vertices[1];

  AssignPrimitiveType(primitives[3], TRIANGLE_TYPE);
  primitives[3].triangleProperties->v1=&vertices[0];
  primitives[3].triangleProperties->v2=&vertices[2];
  primitives[3].triangleProperties->v3=&vertices[3];

  AssignPrimitiveType(primitives[4], TRIANGLE_TYPE);
  primitives[4].triangleProperties->v1=&vertices[1];
  primitives[4].triangleProperties->v2=&vertices[3];
  primitives[4].triangleProperties->v3=&vertices[2];

  AssignPrimitiveType(primitives[5], CYLINDER_TYPE);
  primitives[5].cylinderProperties->axis = Y_INFINITE;
  VectorSetXYZ(primitives[5].cylinderProperties->center, -200, 0, 150);

  for(int i=6; i<numPrimitives; i++)
    AssignPrimitiveType(primitives[i], SPHERE_TYPE);
}

void Scene(Primitive *primitives, int numPrimitives, Vector *vertices, int numVertices, LightSource *lightSources, int numLightSources, float currTime)
{
  for(int i=0; i<numPrimitives; i++)
    {
      primitives[i].surface.baseColor.r = 128 * sin(currTime*i) + 128;
      primitives[i].surface.baseColor.g = 128 * sin(currTime*i + 3 + sin(currTime)) + 128;
      primitives[i].surface.baseColor.b = 128 * sin(currTime*i + 2 + 1.5*sin(currTime)) + 128;
      primitives[i].surface.reflectivity=.5 + .5*sin(currTime+i);
    }
  Vector normal;
  VectorSetXYZ(normal, .15, -1, 0); Rotate(normal, 0, currTime, 0);
  primitives[0].planeProperties->normal = normal;
    
  VectorSetXYZ(vertices[0], 0, -100, 50); 	Rotate(vertices[0], currTime*1.4, currTime, currTime*1.2352);
  VectorSetXYZ(vertices[1], 100, 100, 0);	Rotate(vertices[1], currTime*1.4, currTime, currTime*1.2352);
  VectorSetXYZ(vertices[2], 0, 100, 250);	Rotate(vertices[2], currTime*1.4, currTime, currTime*1.2352);
  VectorSetXYZ(vertices[3], -100, 100, 0);	Rotate(vertices[3], currTime*1.4, currTime, currTime*1.2352);
    
  primitives[5].cylinderProperties->radius = 60 + 40*sin(currTime);
    
  for(int i=6; i<numPrimitives; i++)
    {
      VectorSetXYZ(primitives[i].sphereProperties->center, 120 * sin (currTime+i*2+.56), 120 * sin (currTime+i*2 + 3*sin(currTime*.2)), 120 * sin (currTime+i*5 + 1 + sin(currTime*.1)) );
      primitives[i].sphereProperties->radius= 30 * sin(currTime*.4 + sin(currTime+i)) + 40;
        
    }
    
  for(int i=0; i<numLightSources; i++)
    {
      lightSources[i].location.x = 250*sin(currTime*.5+i);
      lightSources[i].location.y = -100;
      lightSources[i].location.z = 250*cos(currTime*.5+i); 
      lightSources[i].color.r = .15 * sin(currTime + i) + .3;
      lightSources[i].color.g = .15 * sin(currTime + 3 + sin(currTime + i)) + .3;
      lightSources[i].color.b = .15 * sin(currTime*i + 2 + 1.5*sin(currTime)) + .3;
    }
}

int main (int argc, const char * argv[])
{
  puts("Hola este es el ray tracer de Sebastián Arcila-Valenzuela,espero que ponga los datos de configuración que desea");
  // allocate back buffer
  unsigned int* backBuffer = new unsigned int[640*480];
    
  // allocate the ray direction lookup table
  Vector *directionTable = GenerateRayDirectionTable();
  
  puts("(entero>=0) esferas:");
  int numSphere;
  scanf("%d",&numSphere);
  const int numPrimitives = 6+numSphere;
  Primitive *primitives = new Primitive[numPrimitives];


  puts("(entero>=0) fuentes de luz");
  int numLight;
  scanf("%d",&numLight);
  const int numLightSources = numLight;
  LightSource *lightSources = new LightSource[numLightSources];
    

  const int numVertices = 20;
  Vector *vertices = new Vector[numVertices];
  
  SetupScene(primitives, numPrimitives, vertices, numVertices, lightSources, numLightSources);
  
  double seed;
  puts("semilla");
  scanf("%lf",&seed);
  Scene(primitives, numPrimitives, vertices, numVertices, lightSources, numLightSources, seed*.5);

  TraceScene(primitives, numPrimitives, lightSources, numLightSources, backBuffer, directionTable);

  
  // clean up
  for(int i=0; i<numPrimitives; i++) ClearPrimitiveType(primitives[i]);    
  delete[] lightSources;
  delete[] vertices;
  delete[] directionTable;
  delete[] backBuffer;
  return 0;
}
