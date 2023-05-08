#ifndef PARAM_DATA_H
#define PARAM_DATA_H

#include <string>
#include <vector>
#include <list>
#include <map>
#include <glm/glm.hpp>
#include <iostream>


struct Param_data{
  //---------------------------

  bool with_glyph_grid = true;
  std::string path_initial_object_ = "../media/viking_room.obj";
  std::string path_initial_object = "../media/fused.ply";
  std::string path_initial_texture = "../media/viking_room.png";

  //---------------------------
};

#endif
