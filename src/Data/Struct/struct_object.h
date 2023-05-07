#ifndef OBJECT_STRUCT_H
#define OBJECT_STRUCT_H

#include <string>
#include <vector>
#include <list>
#include <map>
#include <glm/glm.hpp>
#include <iostream>
#include <vulkan/vulkan.h>
#include <Eigen/Dense>


struct Object{ //Cloud cloud / part
  //---------------------------

  //State
  int ID = -1;
  int nb_point = 0;
  bool is_visible = true;

  //Drawing
  int draw_type;
  int draw_point_size;
  int draw_line_width;

  //Infos
  std::string name = "";
  std::string path_file;
  std::string path_save;
  std::string path_texture;
  std::string file_format;
  std::string draw_type_name;
  glm::vec4 unicolor;

  //Data
  std::vector<glm::vec3> xyz;
  std::vector<glm::vec4> rgb;
  std::vector<glm::vec3> Nxyz;
  std::vector<glm::vec2> uv;
  std::vector<float> ts;
  std::vector<float> Is;

  bool has_color;
  bool has_intensity;
  bool has_normal;
  bool has_texture;
  bool has_timestamp;

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
  glm::vec3 min = glm::vec3(0.0f);
  glm::vec3 max = glm::vec3(0.0f);
  glm::vec3 root = glm::vec3(0.0f);
  glm::vec3 COM = glm::vec3(0.0f);
  glm::mat4 rotat = glm::mat4(1.0f);
  glm::mat4 trans = glm::mat4(1.0f);
  glm::mat4 scale = glm::mat4(1.0f);
  glm::mat4 transformation = glm::mat4(1.0f);

  //---------------------------
};

#endif