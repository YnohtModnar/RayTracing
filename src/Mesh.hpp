#ifndef MESH_HPP
#define MESH_HPP

#include <opencv2/core.hpp>
#include <iostream>
#include "utils.hpp"

struct Vertex
{
  Vec3f position;

  Vec3f normal;

  Vec2f texCoords;

  Vec3f tangent;

  Vec3f bitangent;
};

struct Triangle
{
  unsigned int v0, v1, v2;
  Vertex* V0;
  Vertex* V1;
  Vertex* V2;
};


struct Texture {
    unsigned int id;
    std::string type;
    std::string path;
    cv::Mat image;
    unsigned char* buffer;
    int height, width, channels;
};

class Mesh
{
public:
  std::vector<Vertex> vertices;
  std::vector<unsigned int> indices;
  std::vector<Triangle> triangles;
  std::vector<Texture> textures;


  Vec3f color;
  float shininess;

  Translation translation;
  Scale scale;
  Rotation rotation;

  Mesh(){
    this->rotation = Rotation();
    this->translation = Translation(0,0,0);
    this->scale = Scale(1.f,1.f,1.f);
    this->shininess = 0.f;
    this->color = Vec3f(150.f,150.f,150.f);
  };


  Mesh(
    std::vector<Vertex> vertices,
    std::vector<unsigned int> indices,
    std::vector<Triangle> triangles,
    std::vector<Texture> textures)
  {
      this->rotation = Rotation();
      this->translation = Translation(0,0,0);
      this->scale = Scale(1.f,1.f,1.f);
      this->shininess = 0.f;
      this->color = Vec3f(150.f,150.f,150.f);
      this->vertices = vertices;
      this->indices = indices;
      this->textures = textures;
      std::vector<Triangle> t;
      for(auto triangle : triangles)
      {
        triangle.V0 = &this->vertices.at(triangle.v0);
        triangle.V1 = &this->vertices.at(triangle.v1);
        triangle.V2 = &this->vertices.at(triangle.v2);
        t.push_back(triangle);
      }
      this->triangles.swap(t);

  }

  void setColor(Vec3f c)
  {color = c;}


  cv::Vec3b getDiffuse(Triangle& triangle, float u, float v)
  {
    int i(0);
    cv::Vec3b c(color.x,color.y,color.z);
    auto texv0c = triangle.V0->texCoords;
    auto texv1c = triangle.V1->texCoords;
    auto texv2c = triangle.V2->texCoords;
    auto texc = texv0c +  (u*(texv1c - texv0c) + v*(texv2c-texv0c));
    for(auto& texture : textures)
      if(texture.type == "texture_diffuse")
      {
        auto y = texture.height-texture.height*texc.y;
        auto x = texture.width*texc.x;
        c[0] = (unsigned char)texture.buffer[texture.channels*(texture.width*int(y)+int(x))];
        c[1] = (unsigned char)texture.buffer[texture.channels*(texture.width*int(y)+int(x))+1];
        c[2] = (unsigned char)texture.buffer[texture.channels*(texture.width*int(y)+int(x))+2];
      }
    return c;
  }


  Vec3f getNormal(Triangle& triangle, float u, float v)
  {
    int i(0);
    Vec3f vector(0,0,0);
    vector = (triangle.V0->normal + triangle.V1->normal + triangle.V2->normal)/3.f;
    auto texv0c = triangle.V0->texCoords;
    auto texv1c = triangle.V1->texCoords;
    auto texv2c = triangle.V2->texCoords;
    auto texc = texv0c +  (u*(texv1c - texv0c) + v*(texv2c-texv0c));
    for(auto& texture : textures)
      if(texture.type == "texture_normal")
      {
        auto y = texture.height-texture.height*texc.y;
        auto x = texture.width*texc.x;
        vector.x += (unsigned char)texture.buffer[texture.channels*(texture.width*int(y)+int(x))];
        vector.y += (unsigned char)texture.buffer[texture.channels*(texture.width*int(y)+int(x))+1];
        vector.z += (unsigned char)texture.buffer[texture.channels*(texture.width*int(y)+int(x))+2];
      }

    return normalize(vector);
  }

  float getSpecular(Triangle& triangle, float u, float v)
  {
    cv::Vec3b vector(0,0,0);
    float value = shininess;
    auto texv0c = triangle.V0->texCoords;
    auto texv1c = triangle.V1->texCoords;
    auto texv2c = triangle.V2->texCoords;
    auto texc = texv0c +  (u*(texv1c - texv0c) + v*(texv2c-texv0c));
    for(auto& texture : textures)
      if(texture.type == "texture_specular")
      {
        auto y = texture.height-texture.height*texc.y;
        auto x = texture.width*texc.x;
        value+=(float)texture.buffer[texture.width*int(y)+int(x)]/255.f;
      }
    return value;
  }

private:

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
