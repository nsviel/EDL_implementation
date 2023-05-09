#ifndef GLYPHS_H
#define GLYPHS_H

#include "Base/Glyph_source.h"
#include "../../common.h"

class Node_data;
class GPU_data;
class Database;


class Glyphs
{
public:
  //Constructor / Destructor
  Glyphs(Node_data* node_data);
  ~Glyphs();

public:
  //Main functions
  void create_glyph_scene();
  Glyph_source* get_glyph_src_byName(string name);

private:
  Node_data* node_data;
  GPU_data* gpu_data;
  Database* dataManager;

  vector<Glyph_source*> vec_glyph_src;
};

#endif
