#ifndef OBJ_IMPORTER_H
#define OBJ_IMPORTER_H

#include "../../../common.h"


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
  Data_file* Loader(string filePath);

  //Subfunction
  void init_params();
  vector<Vertex> get_data_from_file(istream& in);
  void parse_mtl(string path_obj);
  void fill_data_file(Data_file* data, vector<Vertex>& vertex_vec);

private:
  Data_file* data_out;
  string file_mtl;
  string file_texture;
  bool is_face;
};

#endif
