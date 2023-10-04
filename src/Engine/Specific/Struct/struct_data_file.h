#ifndef DATAFILE_STRUCT_H
#define DATAFILE_STRUCT_H

#include <glm/glm.hpp>
#include <string>
#include <vector>


//Generique structure to parse file point clouds
struct Data_file{
  //---------------------------

  //Info
  int nb_element;
  std::string name;
  std::string path_file;
  std::string path;
  std::string draw_type_name;

  //Data
  std::vector<glm::vec3> xyz;
  std::vector<glm::vec3> Nxyz;
  std::vector<glm::vec4> rgb;
  std::vector<glm::vec2> uv;

  std::vector<float> ts;
  std::vector<float> Is;
  std::vector<float> R;
  std::vector<float> A;

  std::vector<Data_file*> vec_data;

  //---------------------------
};


#endif
