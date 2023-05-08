#ifndef FILE_OBJ_H
#define FILE_OBJ_H

#include "../../common.h"


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


class file_OBJ
{
public:
  //Constructor / Destructor
  file_OBJ();
  ~file_OBJ();

public:
  //Main function
  Data* Loader(string filePath);

  //Subfunction
  void init_params();
  vector<Vertex> get_data_from_file(istream& in);
  void parse_mtl(string path_obj);
  void fill_data_file(Data* data, vector<Vertex>& vertex_vec);

private:
  Data* data_out;
  string file_mtl;
  string file_texture;
  bool is_face;
};

#endif
