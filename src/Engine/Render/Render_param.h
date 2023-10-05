#ifndef PARAM_RENDER_H
#define PARAM_RENDER_H

#include "Camera/struct_camera.h"

#include <string>
#include <vector>
#include <list>
#include <map>
#include <glm/glm.hpp>
#include <iostream>


struct Render_param{
  //---------------------------

  int max_fps = 120;
  glm::vec4 background_color = glm::vec4(0.4, 0.4, 0.4, 1);

  Struct_camera camera;

  //---------------------------
};

#endif
