#ifndef GLYPHS_H
#define GLYPHS_H

#include "Base/Glyph_source.h"
#include "../Data_common.h"

class Data_node;
class GPU_data;
class Scene;


class Glyphs
{
public:
  //Constructor / Destructor
  Glyphs(Data_node* data_node);
  ~Glyphs();

public:
  //Main functions
  void create_glyph_scene();
  Glyph_source* get_glyph_src_byName(string name);

private:
  Data_node* data_node;
  GPU_data* gpu_data;
  Scene* sceneManager;

  vector<Glyph_source*> vec_glyph_src;
};

#endif
