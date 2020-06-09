#ifndef RAYCASTER_HPP
#define RAYCASTER_HPP

#include "utils.hpp"
#include "Camera.hpp"
#include "Model.hpp"
#include "Ray.hpp"

#include <iostream>
#include <thread>

#include <opencv2/core.hpp>

struct Light
{
    Vec3f position;
    cv::Vec3b color;
    float brightness;
};


class RayCaster
{
public:
    Camera cam;
    std::vector<Model*> models;
    std::vector<Light> lights;
    cv::Mat image = cv::Mat(480,640,CV_8U);

    float RAYMAXLENGTTH = 5.f;
    float RAYSTEP = 0.1f;

    RayCaster(){
    }

    cv::Vec3b trace(Ray ray, int depth)
    {
      Mesh interMesh;
      Triangle interTriangle;
      float t,u,v;
      float temp_u, temp_v;
      float min = 999999.f;
      bool intersected = false;
      cv::Vec3b color(-1,-1,-1);

      Vec3f rayPos = ray.origin + ray.length*ray.direction;
      //auto& mesh = model->meshes[3];
      for(auto& model : models)
        for(auto& mesh : model->meshes)
          for(auto& triangle : mesh.triangles)
          {
            Vec3f v0 =model->position + (mesh.translation * (mesh.rotation * (mesh.scale * triangle.V0->position)));
            Vec3f v1 =model->position + (mesh.translation * (mesh.rotation * (mesh.scale * triangle.V1->position)));
            Vec3f v2 =model->position + (mesh.translation * (mesh.rotation * (mesh.scale * triangle.V2->position)));
            bool inter = intersect(ray.origin,ray.direction,v0, v1, v2, temp_u, temp_v, t);
            if(inter){
              if(t<min){
                min =t;
                u = temp_u;
                v = temp_v;
                intersected = true;
                interTriangle = triangle;
                interMesh = mesh;
              }
            }
          }
      // Get intersected triangle diffuse color
      if(intersected)
      {
        color = interMesh.getDiffuse(interTriangle, u, v);
      }

      Vec3f pHit = ray.origin + min*ray.direction;
      //Compute Reflection
      if(intersected && depth<1)
      {
        auto N = interMesh.getNormal(interTriangle, u, v);
        float Ks = interMesh.getSpecular(interTriangle, u, v);
        //for(auto light : lights){
          auto L = -(N * pHit);
          auto R = pHit + (L * 2)* N;
          R = normalize(R);
//          raydir - nhit * 2 * raydir.dot(nhit)
          auto reflection = trace(Ray(pHit, R), depth + 1);
          if(reflection!=cv::Vec3b(-1,-1,-1))
            color = (1-Ks)*color + Ks*reflection;
        //}
      }

      // Compute Illumination
      if (intersected) {
        int shadows(0);
        for(auto& light : lights){
          bool isShadow = false;
          Ray shadowRay(pHit, light.position-pHit);
          float dump_u,dump_v,dump_t;
          for(auto& model : models)
            for(auto& mesh : model->meshes)
              for(auto& triangle : mesh.triangles)
              {
                Vec3f v0 = model->position + (mesh.translation * (mesh.rotation * (mesh.scale * triangle.V0->position)));
                Vec3f v1 = model->position + (mesh.translation * (mesh.rotation * (mesh.scale * triangle.V1->position)));
                Vec3f v2 = model->position + (mesh.translation * (mesh.rotation * (mesh.scale * triangle.V2->position)));
                bool inter = intersect(shadowRay.origin, shadowRay.direction, v0, v1, v2, dump_u, dump_v, dump_t);
                if(inter){
                  isShadow = true;
                  break;
                }
              }
          if(!isShadow)
          {
            float l = (light.brightness/(light.brightness+distance(pHit,light.position)));
            color = l*color + (1-l)*color;
          }
          else
            shadows++;
        }
        if(shadows==lights.size())
          color *=0;
      }
      return color;
    }



    void compute()
    {
      std::vector<std::thread*> threads;
      image = cv::Mat::zeros(cam.view.height, cam.view.width, CV_8UC3);
      cv::namedWindow("image",cv::WINDOW_NORMAL);
      for(int y = 0;y<cam.view.height;y++){
        for(int x = 0;x<cam.view.width;x++)
        {
          image.at<cv::Vec3b>(y,x) = cv::Vec3b(255,0,0);
          threads.push_back(new std::thread(caster,this,x,y));
          if(threads.size()>100)
            for(int i(0); i < 100; i++)
              {
                auto t = threads.back();
                t->join();
                threads.pop_back();
              }
        }
        cv::imshow("image",image);
        cv::waitKey(10);
      }
      for(auto t : threads)
        t->join();

    }



    static void caster(RayCaster* rc, int x, int y)
    {
      float u,v, dist;
      cv::Vec3b color(200,200,200);
      rc->image.at<cv::Vec3b>(y,x) = rc->trace(Ray(rc->cam.rayOrigin(x,y),rc->cam.direction(x,y)),0);
    }


    bool intersect(Vec3f& p, Vec3f& d, Vec3f& A, Vec3f& B, Vec3f& C, float &u, float &v,float &t){
      Vec3f e1,e2,h,s,q;
    	float a,f;
    	e1 = B-A;
    	e2 = C-A;

    	h = d.cross(e2);
    	a = e1 * h;
    	if (a > -0.00001 && a < 0.00001)
    		return(false);

    	f = 1/a;
    	s = p - A;
    	u = f * (s*h);

    	if (u < 0.0 || u > 1.0)
    		return(false);

    	q = s.cross(e1);
    	v = f * (d*q);

    	if (v < 0.0 || u + v > 1.0)
    		return(false);

    	// at this stage we can compute t to find out where
    	// the intersection point is on the line
    	t = f * (e2*q);

    	if (t > 0.00001) // ray intersection
    		return(true);
    	else // this means that there is a line intersection
        return (false);
    		 // but not a ray intersection
    }

    float distance(Vec3f a, Vec3f b)
    {
      return sqrt(pow(a.x-b.x,2)+pow(a.y-b.y,2)+pow(a.z-b.z,2));
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
