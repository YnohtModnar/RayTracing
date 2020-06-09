#ifndef UTILS_HPP
#define UTILS_HPP

#include <ostream>
#include <string>

class Vec2f
{
public:
  float x;
  float y;

  Vec2f(float a, float b):
  x(a),y(b){}

  Vec2f(float a):
  x(a),y(a){}

  Vec2f():
  x(0.f),y(0.f){}

  friend Vec2f operator-(const Vec2f& v1, const Vec2f& v2) {
    Vec2f res(v1.x-v2.x,v1.y-v2.y);
    return res;
  }
  friend Vec2f operator+(const Vec2f& v1, const Vec2f& v2) {
    Vec2f res(v1.x+v2.x,v1.y+v2.y);
    return res;
  }
  friend Vec2f operator*(const float value, const Vec2f& v1) {
    Vec2f res(v1.x*value,v1.y*value);
    return res;
  }

  friend std::ostream & operator<<(std::ostream& os, const Vec2f& v) {
    os << "(" << v.x << " ," << v.y << ")";
  }
};

class Vec3f
{
public:
  float x;
  float y;
  float z;

  Vec3f(float a, float b, float c):
  x(a),y(b),z(c){}

  Vec3f(float a):
  x(a),y(a),z(a){}

  Vec3f():
  x(0.f),y(0.f),z(0.f){}


  friend std::ostream & operator<<(std::ostream& os, const Vec3f& v) {
    os << "(" << v.x << " ," << v.y << " ," << v.z << ")";
  }

  friend Vec3f operator-(const Vec3f& v1, const Vec3f& v2) {
    Vec3f res(v1.x-v2.x,v1.y-v2.y,v1.z-v2.z);
    return res;
  }
  friend Vec3f operator+(const Vec3f& v1, const Vec3f& v2) {
    Vec3f res(v1.x+v2.x,v1.y+v2.y,v1.z+v2.z);
    return res;
  }
  friend Vec3f operator*(const float value, const Vec3f& v1) {
    Vec3f res(v1.x*value,v1.y*value,v1.z*value);
    return res;
  }

  friend Vec3f operator*(const Vec3f& v1, const float value) {
    Vec3f res(v1.x*value,v1.y*value,v1.z*value);
    return res;
  }

  friend Vec3f operator/(const Vec3f& v1, const float value) {
    Vec3f res(v1.x/value,v1.y/value,v1.z/value);
    return res;
  }

  Vec3f cross(const Vec3f& v2) {
    float cx = y*v2.z - z*v2.y;
    float cy = z*v2.x - x*v2.z;
    float cz = x*v2.y - y*v2.x;
    return Vec3f(cx,cy,cz);
  }

  friend float operator*(const Vec3f& v2, const Vec3f& v1) {
    return v1.x*v2.x+v1.y*v2.y+v1.z*v2.z;
  }

};

class Vec4f
{
public:
  float x;
  float y;
  float z;
  float w;

  Vec4f(float a, float b, float c, float d):
  x(a),y(b),z(c),w(d){}

  Vec4f(float a):
  x(a),y(a),z(a),w(a){}

  Vec4f():
  x(0.f),y(0.f),z(0.f),w(0.f){}

  friend std::ostream & operator<<(std::ostream& os, const Vec4f& v) {
    os << "(" << v.x << " ," << v.y << " ," << v.z << " ," << v.w << ")";
  }
};

class mat4
{
public:

  mat4()
  {
    x = Vec4f(1,0,0,0);
    y = Vec4f(0,1,0,0);
    z = Vec4f(0,0,1,0);
    w = Vec4f(0,0,0,1);
  }

  friend Vec3f operator*(const mat4& m, const Vec3f& v) {
    float x = m.x.x*v.x + m.y.x*v.y + m.z.x*v.z + m.w.x;
    float y = m.x.y*v.x + m.y.y*v.y + m.z.y*v.z + m.w.y;
    float z = m.x.z*v.x + m.y.z*v.y + m.z.z*v.z + m.w.z;
    return Vec3f(x,y,z);
  }

  friend std::ostream & operator<<(std::ostream& os, const mat4& v) {
    os << v.x << "\n" << v.y << "\n" << v.z << "\n" << v.w;
  }

  Vec4f x;
  Vec4f y;
  Vec4f z;
  Vec4f w;
};

class Translation : public mat4
{
public:
  Translation(float tx =0, float ty = 0, float tz = 0)
  {
    mat4();
    w.x = tx;
    w.y = ty;
    w.z = tz;
  }

};

class Scale : public mat4
{
public:
  Scale(float sx = 1, float sy = 1, float sz = 1)
  {
    mat4();
    x.x = sx;
    y.y = sy;
    z.z = sz;
  }

};

class Rotation
{
public:
  mat4 Rx;
  mat4 Ry;
  mat4 Rz;

  Rotation(float rx = 0, float ry = 0, float rz = 0)
  {
    setRx(rx);
    setRy(ry);
    setRz(rz);
  }

  void setRx(float alpha)
  {
    Rx.x = Vec4f(1,0,0,0);
    Rx.y = Vec4f(0,cos(alpha),-sin(alpha),0);
    Rx.z = Vec4f(0,sin(alpha),cos(alpha),0);
    Rx.w = Vec4f(0,0,0,1);
  }

  void setRy(float alpha)
  {
    Ry.x = Vec4f(cos(alpha),0,sin(alpha),0);
    Ry.y = Vec4f(0,1,0,0);
    Ry.z = Vec4f(-sin(alpha),0,cos(alpha),0);
    Ry.w = Vec4f(0,0,0,1);
  }

  void setRz(float alpha)
  {
    Rz.x = Vec4f(cos(alpha),-sin(alpha),0,0);
    Rz.y = Vec4f(sin(alpha),cos(alpha),0,0);
    Rz.z = Vec4f(0,0,1,0);
    Rz.w = Vec4f(0,0,0,1);
  }

  friend Vec3f operator*(const Rotation& m, const Vec3f& v) {
    return (m.Rx*(m.Ry*(m.Rz*v)));
  }

};


#endif
