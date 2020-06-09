#ifndef SPHERE
#define SPHERE

#include "Mesh.hpp"

class Sphere : public Mesh
{
public:
  Sphere(float r = 1.f):r(r)
  {
    create()
  }

private:
  float r;


  void create()
  {
    
  }
};


#endif
