#ifndef PARAM_ENGINE_H
#define PARAM_ENGINE_H

#include <string>
#include <vector>
#include <list>
#include <map>
#include <glm/glm.hpp>
#include <iostream>


struct Param_engine{
  //---------------------------

  std::string title = "Nephos";

  int max_fps = 120;
  int MAX_FRAMES_IN_FLIGHT = 2;

  glm::vec4 background_color_ = glm::vec4(0.01, 0.01, 0.01, 1);
  glm::vec4 background_color = glm::vec4(0.262, 0.262, 0.262, 1);
  glm::vec2 window_dim = glm::vec2(1024, 500);
  glm::vec2 window_dim_min = glm::vec2(500, 250);

  std::string path_shader_vs = "../src/Engine/Shader/spir/vert.spv";
  std::string path_shader_fs = "../src/Engine/Shader/spir/frag.spv";

  //---------------------------
};

#endif
