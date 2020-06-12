#ifndef CUBE_H
#define CUBE_H

#include "Mesh.hpp"

class Cube : public Mesh
{
public:
  Cube()
  {
    Mesh();
    create();
    color = Vec3f(200.f,200.f,200.f);
  }

private:

  void create()
  {
    Vertex v;
    Vec3f v0p, v1p, v2p, v3p, v4p, v5p, v6p, v7p;
    Vec3f v0n, v1n, v2n, v3n, v4n, v5n, v6n, v7n;
    Triangle t;


    v0p = Vec3f(0.5f, -0.5f,-0.5f);
    v1p = Vec3f(0.5f, -0.5f, 0.5f);
    v2p = Vec3f(-0.5f,-0.5f, 0.5f);
    v3p = Vec3f(-0.5f,-0.5f,-0.5f);
    v4p = Vec3f(0.5f, 0.5f, -0.5f);
    v5p = Vec3f(0.5f, 0.5f, 0.5f);
    v6p = Vec3f(-0.5f,0.5f, 0.5f);
    v7p = Vec3f(-0.5f, 0.5f, -0.5f);

    v0n = Vec3f(0.f,0.f,-1.f);
    v1n = Vec3f(-1.f,0.f,0.f);
    v2n = Vec3f(0.f,0.f,-1.f);
    v3n = Vec3f(0.f,0.f,1.f);
    v4n = Vec3f(1.f,0.f,0.f);
    v5n = Vec3f(1.f,0.f,0.f);
    v6n = Vec3f(0.f,1.f,0.f);
    v7n = Vec3f(0.f,-1.f,0.f);


    v.position = v4p;
    v.normal = v0n;
    vertices.push_back(v);
    v.position = v0p;
    v.normal = v0n;
    vertices.push_back(v);
    v.position = v3p;
    v.normal = v0n;
    vertices.push_back(v);
    v.position = v7p;
    v.normal = v0n;
    vertices.push_back(v);
    v.position = v2p;
    v.normal = v1n;
    vertices.push_back(v);
    v.position = v6p;
    v.normal = v1n;
    vertices.push_back(v);
    v.position = v7p;
    v.normal = v1n;
    vertices.push_back(v);
    v.position = v3p;
    v.normal = v1n;
    vertices.push_back(v);
    v.position = v1p;
    v.normal = v2n;
    vertices.push_back(v);
    v.position = v5p;
    v.normal = v2n;
    vertices.push_back(v);
    v.position = v2p;
    v.normal = v2n;
    vertices.push_back(v);
    v.position = v5p;
    v.normal = v3n;
    vertices.push_back(v);
    v.position = v6p;
    v.normal = v3n;
    vertices.push_back(v);
    v.position = v2p;
    v.normal = v3n;
    vertices.push_back(v);
    v.position = v0p;
    v.normal = v4n;
    vertices.push_back(v);
    v.position = v4p;
    v.normal = v4n;
    vertices.push_back(v);
    v.position = v1p;
    v.normal = v4n;
    vertices.push_back(v);
    v.position = v4p;
    v.normal = v5n;
    vertices.push_back(v);
    v.position = v5p;
    v.normal = v5n;
    vertices.push_back(v);
    v.position = v1p;
    v.normal = v5n;
    vertices.push_back(v);
    v.position = v4p;
    v.normal = v6n;
    vertices.push_back(v);
    v.position = v7p;
    v.normal = v6n;
    vertices.push_back(v);
    v.position = v5p;
    v.normal = v6n;
    vertices.push_back(v);
    v.position = v6p;
    v.normal = v6n;
    vertices.push_back(v);
    v.position = v0p;
    v.normal = v7n;
    vertices.push_back(v);
    v.position = v1p;
    v.normal = v7n;
    vertices.push_back(v);
    v.position = v2p;
    v.normal = v7n;
    vertices.push_back(v);
    v.position = v3p;
    v.normal = v7n;
    vertices.push_back(v);



    t.v0 = 0;
    t.v1 = 1;
    t.v2 = 2;
    t.V0 = &(vertices.at(0));
    t.V1 = &(vertices.at(1));
    t.V2 = &(vertices.at(2));
    triangles.push_back(t);

    t.v0 = 0;
    t.v1 = 2;
    t.v2 = 3;
    t.V0 = &(vertices.at(0));
    t.V1 = &(vertices.at(2));
    t.V2 = &(vertices.at(3));
    triangles.push_back(t);



    t.v0 = 4;
    t.v1 = 5;
    t.v2 = 6;
    t.V0 = &(vertices.at(4));
    t.V1 = &(vertices.at(5));
    t.V2 = &(vertices.at(6));
    triangles.push_back(t);

    t.v0 = 4;
    t.v1 = 6;
    t.v2 = 7;
    t.V0 = &(vertices.at(4));
    t.V1 = &(vertices.at(6));
    t.V2 = &(vertices.at(7));
    triangles.push_back(t);

    t.v0 = 8;
    t.v1 = 9;
    t.v2 = 10;
    t.V0 = &(vertices.at(8));
    t.V1 = &(vertices.at(9));
    t.V2 = &(vertices.at(10));
    triangles.push_back(t);

    t.v0 = 11;
    t.v1 = 12;
    t.v2 = 13;
    t.V0 = &(vertices.at(11));
    t.V1 = &(vertices.at(12));
    t.V2 = &(vertices.at(13));
    triangles.push_back(t);

    t.v0 = 14;
    t.v1 = 15;
    t.v2 = 16;
    t.V0 = &(vertices.at(14));
    t.V1 = &(vertices.at(15));
    t.V2 = &(vertices.at(16));
    triangles.push_back(t);

    t.v0 = 17;
    t.v1 = 18;
    t.v2 = 19;
    t.V0 = &(vertices.at(17));
    t.V1 = &(vertices.at(18));
    t.V2 = &(vertices.at(19));
    triangles.push_back(t);

    t.v0 = 20;
    t.v1 = 21;
    t.v2 = 22;
    t.V0 = &(vertices.at(20));
    t.V1 = &(vertices.at(21));
    t.V2 = &(vertices.at(22));
    triangles.push_back(t);

    t.v0 = 21;
    t.v1 = 23;
    t.v2 = 22;
    t.V0 = &(vertices.at(21));
    t.V1 = &(vertices.at(23));
    t.V2 = &(vertices.at(22));
    triangles.push_back(t);

    t.v0 = 24;
    t.v1 = 25;
    t.v2 = 26;
    t.V0 = &(vertices.at(24));
    t.V1 = &(vertices.at(25));
    t.V2 = &(vertices.at(26));
    triangles.push_back(t);

    t.v0 = 24;
    t.v1 = 26;
    t.v2 = 27;
    t.V0 = &(vertices.at(24));
    t.V1 = &(vertices.at(26));
    t.V2 = &(vertices.at(27));
    triangles.push_back(t);




  }
};


#endif
