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
  std::string path_initial_object = "../src/Engine/Texture/viking_room.obj";
  std::string path_initial_texture = "../src/Engine/Texture/viking_room.png";
  
  //---------------------------
};

#endif
