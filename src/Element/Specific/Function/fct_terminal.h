#ifndef TERMINAL_FUNCTIONS_H
#define TERMINAL_FUNCTIONS_H

#include <iostream>
#include <time.h>
#include <string>
#include <vector>
#include <chrono>
#include <iomanip>
#include <list>
#include <Eigen/Dense>


namespace{
  //Variable terminal output
  template<typename Type>
  void say(Type truc){
    //---------------------------

    std::cout<< "-> " << truc <<std::endl;

    //---------------------------
  }
  void say(const glm::mat4 m){
    //---------------------------

    std::cout << m[0][0] << " " << m[0][1] << " " << m[0][2] << " " << m[0][3] << std::endl;
    std::cout << m[1][0] << " " << m[1][1] << " " << m[1][2] << " " << m[1][3] << std::endl;
    std::cout << m[2][0] << " " << m[2][1] << " " << m[2][2] << " " << m[2][3] << std::endl;
    std::cout << m[3][0] << " " << m[3][1] << " " << m[3][2] << " " << m[3][3] << std::endl;

    //---------------------------
  }
  void say(glm::vec2 truc){
    //---------------------------

    std::cout<< "-> " << truc[0] <<" "<< truc[1] <<std::endl;

    //---------------------------
  }
  void say(glm::vec3 truc){
    //---------------------------

    std::cout<< "-> " << truc[0] <<" "<< truc[1] <<" "<< truc[2] <<std::endl;

    //---------------------------
  }
  void say(Eigen::Vector3d truc){
    //---------------------------

    std::cout<< "-> " << truc(0) <<" "<< truc(1) <<" "<< truc(2) <<std::endl;

    //---------------------------
  }
  void say(std::vector<glm::vec2> truc){
    //---------------------------

    for(int i=0; i<truc.size(); i++){
      std::cout<<"line."<<i<<" -> "<< truc[i].x <<" "<< truc[i].y <<std::endl;
    }

    //---------------------------
  }
  void say(std::vector<glm::vec3> truc){
    //---------------------------

    for(int i=0; i<truc.size(); i++){
      std::cout<<"line."<<i<<" -> "<< truc[i].x <<" "<< truc[i].y <<" "<< truc[i].z <<std::endl;
    }

    //---------------------------
  }
  void say(std::vector<glm::vec4> truc){
    //---------------------------

    for(int i=0; i<truc.size(); i++){
      std::cout<<"line."<<i<<" -> "<< truc[i].x <<" "<< truc[i].y <<" "<< truc[i].z <<" "<< truc[i].w <<std::endl;
    }

    //---------------------------
  }
  void say(glm::vec4 truc){
    //---------------------------

    std::cout<< "-> " << truc[0] <<" "<< truc[1] <<" "<< truc[2] <<" "<< truc[3] << std::endl;

    //---------------------------
  }
  template<typename Type>
  void say(std::list<Type>& truc){
    //---------------------------

    for(int i=0; i<truc.size(); i++){
      Type type = *next(truc.begin(), i);
      std::cout << std::to_string(i) << ". ->" << type << std::endl;
    }

    //---------------------------
  }

  template<typename Type>
  void saySize(Type truc){
    std::cout<< "-> " << truc.size() <<std::endl;
  }
  template<typename Type>
  void sayVec(std::vector<Type>& vec){
    for(int i=0; i<vec.size(); i++){
      std::cout<<std::fixed<<std::setprecision(5)<<"line."<<i<<" -> "<<vec[i]<<std::endl;
    }
  }

  void sayMean(std::vector<glm::vec3> truc){
    glm::vec3 mean = glm::vec3(0, 0, 0);
    for(int i=0; i<truc.size(); i++){
      mean.x += truc[i].x;
      mean.y += truc[i].y;
      mean.z += truc[i].z;
    }
    mean.x = mean.x / truc.size();
    mean.y = mean.y / truc.size();
    mean.z = mean.z / truc.size();
    std::cout<< "mean-> " << mean[0] <<" "<< mean[1] <<" "<< mean[2] <<std::endl;
  }
  void sayHello(){
    std::cout<<"Hello ! "<<std::endl;
  }
  void wtf(){
    std::cout<<"wtf"<<std::endl;
  }

  //---------------------------
}

#endif
