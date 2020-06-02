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
    std::vector<Model> models;
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
      //auto mesh = model.meshes[3];
      for(auto model : models)
        for(auto mesh : model.meshes)
          for(auto triangle : mesh.triangles)
          {
            Vec3f v0 = mesh.vertices.at(triangle.v0).position+model.position;
            Vec3f v1 = mesh.vertices.at(triangle.v1).position+model.position;
            Vec3f v2 = mesh.vertices.at(triangle.v2).position+model.position;
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
        color = getDiffuse(interMesh, interTriangle, u, v);
      }

      Vec3f pHit = ray.origin + min*ray.direction;
      //Compute Reflection
      if(intersected && depth<5)
      {
        auto N = getNormal(interMesh, interTriangle, u, v);
        float Ks = getSpecular(interMesh, interTriangle, u, v);
        for(auto light : lights){
          auto L = light.position-pHit;
          auto R = (2*(L*N))*N - L;
          auto reflection = trace(Ray(pHit + N, L), depth + 1);
          if(reflection!=cv::Vec3b(-1,-1,-1))
            color = (1-Ks)*color + Ks*reflection;
        }
      }
        //std::cout << "NHit " << nhit << std::endl;
        //std::cout << "V0 " << interMesh.vertices.at(interTriangle.v0).normal << std::endl;
        //std::cout << "V1 " << interMesh.vertices.at(interTriangle.v1).normal << std::endl;
        //std::cout << "V2 " << interMesh.vertices.at(interTriangle.v2).normal << std::endl;
        //Vec3f nhit = interMesh.vertices.at(interTriangle.v0).normal+interMesh.vertices.at(interTriangle.v1).normal+interMesh.vertices.at(interTriangle.v2).normal;
        //nhit.x/=3;
        //nhit.y/=3;
        //nhit.z/=3;
        /*bool inside = false;
        if (ray.direction*nhit > 0) nhit = Vec3f(0)-nhit, inside = true;
        auto spec = getSpecular(interMesh, interTriangle, u, v);

        Vec3f refldir = ray.direction - nhit * (2 * (ray.direction*nhit));
        refldir = normalize(refldir);
        auto reflection = trace(Ray(pHit + nhit, refldir), depth + 1);

        //float Kds = (spec.x+spec.y+spec.z)/3.f;
        if(reflection!=cv::Vec3b(-1,-1,-1))
          color = (1-spec)*color + spec*reflection;
        //return color;
      }*/

      // Compute Illumination
      if (intersected) {
        int shadows(0);
        for(auto light : lights){
          bool isShadow = false;
          Ray shadowRay(pHit, light.position-pHit);
          float dump_u,dump_v,dump_t;
          for(auto model : models)
            for(auto mesh : model.meshes)
              for(auto triangle : mesh.triangles)
              {
                Vec3f v0 = mesh.vertices.at(triangle.v0).position+model.position;
                Vec3f v1 = mesh.vertices.at(triangle.v1).position+model.position;
                Vec3f v2 = mesh.vertices.at(triangle.v2).position+model.position;
                bool inter = intersect(shadowRay.origin,shadowRay.direction,v0, v1, v2, dump_u, dump_v, dump_t);
                if(inter){
                  isShadow = true;
                  break;
                }
              }
          if(!isShadow)
          {
            color=color*(light.brightness/distance(pHit,light.position));
          }
          else
            shadows++;
        }
        if(shadows==lights.size())
          color *=0.1;
      }
      return color;
    }


    cv::Vec3b getDiffuse(Mesh mesh, Triangle triangle, float u, float v)
    {
      int i(0);
      cv::Vec3b color(0,0,0);
      auto texv0c = mesh.vertices.at(triangle.v0).texCoords;
      auto texv1c = mesh.vertices.at(triangle.v1).texCoords;
      auto texv2c = mesh.vertices.at(triangle.v2).texCoords;
      auto texc = texv0c +  (u*(texv1c - texv0c) + v*(texv2c-texv0c));
      for(auto texture : mesh.textures)
        if(texture.type == "texture_diffuse")
        {
          auto y = texture.height-texture.height*texc.y;
          auto x = texture.width*texc.x;
          color[0] += (unsigned char)texture.buffer[texture.channels*(texture.width*int(y)+int(x))];
          color[1] += (unsigned char)texture.buffer[texture.channels*(texture.width*int(y)+int(x))+1];
          color[2] += (unsigned char)texture.buffer[texture.channels*(texture.width*int(y)+int(x))+2];
//          std::cout << (float)texture.buffer[(int)texc.y*texture.width] << std::endl;
          /*color += texture.image.at<cv::Vec3b>(
                        texture.image.cols-texture.image.cols*(texc.y),
                        texture.image.rows*(texc.x));
          */i++;
        }
      return i>0?color/i:color;
    }

    Vec3f getNormal(Mesh mesh, Triangle triangle, float u, float v)
    {
      int i(0);
      Vec3f vector(0,0,0);
      auto texv0c = mesh.vertices.at(triangle.v0).texCoords;
      auto texv1c = mesh.vertices.at(triangle.v1).texCoords;
      auto texv2c = mesh.vertices.at(triangle.v2).texCoords;
      auto texc = texv0c +  (u*(texv1c - texv0c) + v*(texv2c-texv0c));
      for(auto texture : mesh.textures)
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

    float getSpecular(Mesh mesh, Triangle triangle, float u, float v)
    {
      int i(0);
      cv::Vec3b vector(0,0,0);
      float value = 0;
      auto texv0c = mesh.vertices.at(triangle.v0).texCoords;
      auto texv1c = mesh.vertices.at(triangle.v1).texCoords;
      auto texv2c = mesh.vertices.at(triangle.v2).texCoords;
      auto texc = texv0c +  (u*(texv1c - texv0c) + v*(texv2c-texv0c));
      for(auto texture : mesh.textures)
        if(texture.type == "texture_specular")
        {
          auto y = texture.height-texture.height*texc.y;
          auto x = texture.width*texc.x;
          value+=(float)texture.buffer[texture.width*int(y)+int(x)]/255.f;
          //std::cout << value << std::endl;
        }

//      return Vec3f(vector[0]/255.f,vector[1]/255.f,vector[2]/255.f);
      return value;
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

    void compute()
    {
      std::vector<std::thread*> threads;
      image = cv::Mat::zeros(cam.view.height, cam.view.width, CV_8UC3);
      cv::namedWindow("image",cv::WINDOW_NORMAL);
      for(int y = 0;y<cam.view.height;y++)
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
      //rc->cast(Ray(rc->cam.rayOrigin(x,y),rc->cam.direction(x,y)),u,v,dist,color);
      rc->image.at<cv::Vec3b>(y,x) = rc->trace(Ray(rc->cam.rayOrigin(x,y),rc->cam.direction(x,y)),0);
    }


    bool intersect(Vec3f p, Vec3f d, Vec3f A, Vec3f B, Vec3f C, float &u, float &v,float &t){
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

};


#endif
