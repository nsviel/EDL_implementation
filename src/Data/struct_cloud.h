#ifndef CLOUD_STRUCT_H
#define CLOUD_STRUCT_H

#include <vector>
#include <string>
#include <glm/glm.hpp>
#include <Eigen/Dense>


struct Cloud
{
  //---------------------------

  Cloud();
  void reset();

  //Info
  int nb_element;
  std::string name;
  std::string draw_type;

  //Data
  std::vector<glm::vec3> xyz;
  std::vector<glm::vec4> rgb;
  std::vector<glm::vec3> Nxyz;
  std::vector<glm::vec2> uv;
  std::vector<float> ts;
  std::vector<float> Is;

  //Pose
  Eigen::Matrix3d pose_R;
  Eigen::Vector3d pose_T;

  //---------------------------
};

#endif
