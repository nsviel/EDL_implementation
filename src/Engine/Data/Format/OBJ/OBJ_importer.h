#ifndef OBJ_IMPORTER_H
#define OBJ_IMPORTER_H

#include <Specific/Struct/struct_data_file.h>
#include <Specific/File/Info.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <fstream>


struct Vertex{
  //---------------------------

  glm::vec3 location;
  glm::vec2 texcoord;
  glm::vec3 normal;

  //---------------------------
};
struct Vertex_ref{
  //---------------------------

  Vertex_ref( int v, int vt, int vn ) : v(v), vt(vt), vn(vn) { }
  int v, vt, vn;

  //---------------------------
};


class OBJ_importer
{
public:
  //Constructor / Destructor
  OBJ_importer();
  ~OBJ_importer();

public:
  //Main function
  Data_file* Loader(std::string filePath);

  //Subfunction
  void init_params();
  std::vector<Vertex> get_data_from_file(std::istream& in);
  void parse_mtl(std::string path_obj);
  void fill_data_file(Data_file* data, std::vector<Vertex>& vertex_vec);

private:
  Data_file* data_out;
  std::string file_mtl;
  std::string file_texture;
  bool is_face;
};

#endif
