#ifndef CLOUD_STRUCT_H
#define CLOUD_STRUCT_H

#include "struct_object.h"

#include "../../common.h"


struct Cloud : public Object{
  //---------------------------

  Cloud();
  void reset();

  //Info
  int nb_element;
  std::string name;
  std::string path_file;
  std::string path_texture;
  std::string draw_type;

  //Data
  std::vector<glm::vec3> xyz;
  std::vector<glm::vec4> rgb;
  std::vector<glm::vec3> Nxyz;
  std::vector<glm::vec2> uv;
  std::vector<float> ts;
  std::vector<float> Is;

  //Vulkan stuff
  VkBuffer vbo_xyz;
  VkBuffer vbo_rgb;
  VkBuffer vbo_uv;

  VkDeviceMemory mem_xyz;
  VkDeviceMemory mem_rgb;
  VkDeviceMemory mem_uv;

  //Pose
  Eigen::Matrix3d pose_R;
  Eigen::Vector3d pose_T;

  //---------------------------
};

#endif
