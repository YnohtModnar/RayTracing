#ifndef MESH_HPP
#define MESH_HPP

#include <opencv2/core.hpp>

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

  Mesh(){};

  Mesh(
    std::vector<Vertex> vertices,
    std::vector<unsigned int> indices,
    std::vector<Triangle> triangles,
    std::vector<Texture> textures)
  {
      this->vertices = vertices;
      this->indices = indices;
      this->triangles = triangles;
      this->textures = textures;
  }

};


#endif
