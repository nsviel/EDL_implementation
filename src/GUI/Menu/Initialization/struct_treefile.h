#ifndef GLYPH_STRUCT_H
#define GLYPH_STRUCT_H

#include "../../common.h"


struct Struct_treefile{
  //---------------------------

  string name;
  string type;
  string path;
  float size = -1;
  bool already_open = false;
  bool end_folder;
  int leaf_idx;
  int leaf_nb;

  //---------------------------
};

#endif
