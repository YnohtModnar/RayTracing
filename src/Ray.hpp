#ifndef RAY_HPP
#define RAY_HPP

#include "utils.hpp"

class Ray
{
public:
    Vec3f origin;
    Vec3f direction;
    float length = 0.01f;

    Ray(Vec3f o, Vec3f d):origin(o),direction(d),length(0){}

};


#endif
