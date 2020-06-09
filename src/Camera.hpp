#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "utils.hpp"

struct Eye
{
  Vec3f position;
  Vec3f u;
  Vec3f v;
  Vec3f n;
  Vec3f COI;
  Vec3f v_up;
};

struct View
{
  Vec3f position;
  float FoV;
  float d;
  float H;
  float W;
  Vec3f L;

  float width;
  float height;
};

class Camera
{
public:
  Eye eye;
  View view;

  Camera()
  {
    view.FoV = 45.f;
    Vec3f p(0.f,0.f,3.f);
    Vec3f v_up(0,1,0);
    Vec3f COI(0,0,0);
    view.width = 256;
    view.height = 256;
    view.H = 1;
    eye.position = p;
    eye.COI = COI;
    eye.v_up = v_up;
    compute();
  }

  void compute()
  {
    std::cout << "EYE POS "<< eye.position<<std::endl;
    eye.n = normalize(eye.position - eye.COI);
    eye.u = normalize(eye.v_up.cross(eye.n));
    eye.v = eye.n.cross(eye.u);

    std::cout << " U " << eye.u << std::endl;
    std::cout << " V " << eye.v << std::endl;
    std::cout << " N " << eye.n << std::endl;

    view.d = (view.H / tan(view.FoV/2.f))/2.f;
    view.W = view.H * view.width/view.height;
    view.position = eye.position - eye.n*view.d;
    view.L = view.position - (view.W/2)*eye.u - (view.H/2)*eye.v;
    std::cout << "D " << view.d << std::endl;
    std::cout << "H " << view.H << std::endl;
    std::cout << "W " << view.W << std::endl;
    std::cout << "C " << view.position << std::endl;
    std::cout << "L " << view.L << std::endl;
  }

  void setResolution(int w, int h)
  {
    view.height = h;
    view.width = w;
    compute();
  }

  void setFoV(float fov)
  {
    view.FoV = std::min(std::max(0.f,fov),90.f);
    compute();
  }



  Vec3f rayOrigin(int u, int v)
  {
      Vec3f s=view.L + eye.u * u * (view.W/view.width) + eye.v * v * (view.H/view.height);
      return s;
  }

  Vec3f direction(int u, int v)
  {
      Vec3f s=view.L + eye.u * u * (view.W/view.width) + eye.v * v * (view.H/view.height);
      return normalize(s-eye.position);
  }

  Vec3f normalize(Vec3f v)
  {
    float t = sqrt(pow(v.x,2)+pow(v.y,2)+pow(v.z,2));
    if(t==0)
      return Vec3f(0,0,0);
    v.x /= t;
    v.y /= t;
    v.z /= t;
    return v;
  }


};
#endif
