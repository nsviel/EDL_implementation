#ifndef OBJECT_STRUCT_H
#define OBJECT_STRUCT_H

#include "struct_texture.h"

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

  //Functions
  void reset();

  //State
  int ID = -1;
  int nb_point = 0;
  int draw_line_width;

  //Infos
  std::string name = "";
  std::string path_file = "";
  std::string path_save = "";
  std::string path_text = "";
  std::string file_format = "";
  std::string draw_type_name = "";
  glm::vec4 unicolor;

  //Data
  std::vector<glm::vec3> xyz;
  std::vector<glm::vec4> rgb;
  std::vector<glm::vec3> Nxyz;
  std::vector<glm::vec2> uv;
  std::vector<float> ts;
  std::vector<float> Is;

  bool is_visible = true;
  bool has_color;
  bool has_intensity;
  bool has_normal;
  bool has_texture;
  bool has_timestamp;

  //Pose
  glm::vec3 min = glm::vec3(0.0f);
  glm::vec3 max = glm::vec3(0.0f);
  glm::vec3 root = glm::vec3(0.0f);
  glm::vec3 COM = glm::vec3(0.0f);
  glm::mat4 rotat = glm::mat4(1.0f);
  glm::mat4 trans = glm::mat4(1.0f);
  glm::mat4 scale = glm::mat4(1.0f);
  glm::mat4 model = glm::mat4(1.0f);
  glm::mat4 mvp = glm::mat4(1.0f);

  //---------------------------
};

#endif
