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


#endif
