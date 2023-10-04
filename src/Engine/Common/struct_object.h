#ifndef STRUCT_OBJECT_H
#define STRUCT_OBJECT_H

#include <glm/glm.hpp>
#include <vulkan/vulkan.h>
#include <Eigen/Dense>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>


struct Object{ //Cloud cloud / part
  //---------------------------

  //Functions
  void reset();

  //State
  int ID = -1;
  int nb_point = 0;
  int draw_line_width = 1;
  int draw_point_size = 5;

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
  bool is_suppressible = true;
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

  //List of subobject
  std::list<Object*> list_object;

  //---------------------------
};

#endif
