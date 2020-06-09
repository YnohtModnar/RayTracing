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
#include "Cube.hpp"

int
main(
  int argc,
  char const *argv[])
{

  RayCaster rc;
  Camera c;
  Light light1;
  Light light2;
  std::vector<Vertex> vertices;
  Vertex v;
  Model model;
  model.position = Vec3f(0,0,0);
  Cube cube;
  cube.translation = Translation(-3,0,2);
  cube.shininess = 0.0f;
  cube.setColor(Vec3f(255.f,0.f,0.f));
  cube.rotation.setRx(45);
  cube.rotation.setRy(45);
  model.addMesh(cube);

  Cube cube2;
  cube2.shininess = 0.9f;
  cube2.scale = Scale(10,10,0.5);
  cube2.translation = Translation(0,0,-3);
  model.addMesh(cube2);

  Cube cube3;
  cube3.shininess = 0.9f;
  cube3.scale = Scale(10,0.5,10);
  cube3.translation = Translation(0,2,-1);
  cube3.setColor(Vec3f(0.f,120.f,0.f));
  model.addMesh(cube3);




  light1.position = Vec3f(0,0,10);
  light1.brightness = 2;
  light1.color = cv::Vec3b(0,0,255);
  light2.position = Vec3f(-1,3,11);
  light2.brightness = 2;
  light2.color = cv::Vec3b(255,0,255);

  c.eye.position.x = 0.f;
  c.eye.position.y = 0.f;
  c.eye.position.z = 10.f;
  c.setResolution(512,512);
  //c.setFoV(45);

  rc.cam = c;
  rc.models.push_back(&model);
  rc.lights.push_back(light1);
//  rc.lights.push_back(light2);
  rc.compute();



  std::cout << "END OF PROCESS" << std::endl;
  cv::imshow("Test",rc.image);
  if(argc > 2)
    cv::imwrite(argv[2], rc.image);
  cv::waitKey();

  return 0;
}
