#ifndef DATAFILE_STRUCT_H
#define DATAFILE_STRUCT_H

#include "../common.h"


//Generique structure to parse file point clouds
struct Data{
  //---------------------------

  //Info
  int nb_element;
  std::string name;
  std::string path;
  std::string draw_type;

  //Data
  std::vector<glm::vec3> xyz;
  std::vector<glm::vec3> Nxyz;
  std::vector<glm::vec4> rgb;
  std::vector<glm::vec2> uv;
  std::vector<float> ts;
  std::vector<float> Is;

  //---------------------------
};


#endif
