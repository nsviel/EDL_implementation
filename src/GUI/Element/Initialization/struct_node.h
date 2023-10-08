#ifndef STRUCT_TREEFILE_H
#define STRUCT_TREEFILE_H

#include <Specific/common.h>


struct Tree_node{
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
