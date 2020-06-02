#include <opencv2/highgui.hpp>

#include "Model.hpp"
#include "Mesh.hpp"
#include <iostream>
#include <vector>
#include "Camera.hpp"
#include "RayCaster.hpp"
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>

int
main(
  int argc,
  char const *argv[])
{

  std::vector<Vertex> vertices;
  Vertex v;
  Model model(argv[1]);
  model.position = Vec3f(0,0,0);
  Model model2(argv[1]);
  model2.position = Vec3f(0,0,4);
  /*
  for(auto mesh : model.meshes)
    for(auto text : mesh.textures)
    {
      auto i = text.image.clone();
      for(auto triangle : mesh.triangles)
      {
          cv::circle(i, cv::Point(i.rows*mesh.vertices.at(triangle.v0).texCoords.x,i.cols*mesh.vertices.at(triangle.v0).texCoords.y),10,cv::Scalar(0,255,0));
          cv::circle(i, cv::Point(i.rows*mesh.vertices.at(triangle.v1).texCoords.x,i.cols*mesh.vertices.at(triangle.v1).texCoords.y),10,cv::Scalar(0,255,0));
          cv::circle(i, cv::Point(i.rows*mesh.vertices.at(triangle.v2).texCoords.x,i.cols*mesh.vertices.at(triangle.v2).texCoords.y),10,cv::Scalar(0,255,0));
      }
      cv::namedWindow("Image",cv::WINDOW_NORMAL);
      cv::imshow("Image",i);
      cv::waitKey(10);
    }*/

  Camera c;

  c.setResolution(256,256);

  Light light1;
  light1.position = Vec3f(0.5,0.5,1);
  light1.brightness = 2;
  light1.color = cv::Vec3b(0,0,255);
  Light light2;
  light2.position = Vec3f(-0.5,0.5,1);
  light2.brightness = 2;
  light2.color = cv::Vec3b(255,0,255);
  RayCaster rc;
  rc.cam = c;
  rc.models.push_back(model);
  rc.models.push_back(model2);
  rc.lights.push_back(light1);
  //rc.lights.push_back(light2);
  rc.compute();



  std::cout << "END OF PROCESS" << std::endl;
  cv::imshow("Test",rc.image);
  if(argc > 2)
    cv::imwrite(argv[2], rc.image);
  cv::waitKey();

  return 0;
}
