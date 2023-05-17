#ifndef PARAM_VULKAN_H
#define PARAM_VULKAN_H

#include <string>
#include <vector>
#include <list>
#include <map>
#include <glm/glm.hpp>
#include <iostream>


struct Param_vulkan{
  //---------------------------

  std::string title = "Nephos";

  int max_frame = 2;

  glm::vec2 window_dim = glm::vec2(1024, 500);
  glm::vec2 window_dim_min = glm::vec2(500, 250);

  std::string path_shader_vs = "../src/Engine/Shader/spir/vert.spv";
  std::string path_shader_fs = "../src/Engine/Shader/spir/frag.spv";

  //---------------------------
};

#endif
