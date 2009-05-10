#ifndef vector_h
#define vector_h

#include <math.h>

struct Vector
{
  float x,y,z;
};

inline void VectorSetXYZ(Vector &v, float x, float y, float z)
{
  v.x=x; 
  v.y=y;
  v.z=z;
}
inline Vector VectorAdd(Vector &a, Vector &b)// result = a + b
{
  Vector result;
  result.x = a.x + b.x;
  result.y = a.y + b.y;
  result.z = a.z + b.z;
  return result;
}

inline Vector VectorSub(Vector &a, Vector &b)// result = a - b
{
  Vector result;
  result.x = a.x - b.x;
  result.y = a.y - b.y;
  result.z = a.z - b.z;
  return result;
}

inline float VectorDot(Vector &a, Vector &b)
{
  return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

inline Vector VectorCross(Vector &a, Vector &b)
{
  Vector c;
  c.x = a.y * b.z - a.z * b.y;
  c.y = a.z * b.x - a.x * b.z;
  c.z = a.x * b.y - a.y * b.x; 
  return c;
}

inline void VectorNormalize(Vector &v)
{
  float scaleFactor = 1/sqrt( (v.x * v.x) + (v.y * v.y) + (v.z * v.z) );
  v.x *= scaleFactor;
  v.y *= scaleFactor;
  v.z *= scaleFactor;
}

inline void Rotate(Vector &v, float ax, float ay, float az) 
{										
  Vector temp;
  temp.y=v.y;
        
  v.y = (float)(v.y * cos(ax) - v.z * sin(ax));
  v.z = (float)(v.z * cos(ax) + temp.y * sin(ax));

  temp.z=v.z;
  v.z = (float)(v.z * cos(ay) - v.x * sin(ay));
  v.x = (float)(v.x * cos(ay) + temp.z * sin(ay));
  
  temp.x=v.x;
  v.x = (float)(v.x * cos(az) - v.y * sin(az));
  v.y = (float)(v.y * cos(az) + temp.x * sin(az));

}


#endif
