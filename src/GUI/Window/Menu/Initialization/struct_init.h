#ifndef STRUCT_INIT_H
#define STRUCT_INIT_H

#include "struct_node.h"
#include <Specific/common.h>


struct Struct_init{
  //---------------------------

  bool remove_old = true;
  float scale = 1;

  vector<string> accepted_format;
  vector<string> vec_path_folder;
  vector<string> vec_path_file;

  //Selection
  bool is_selection = false;
  Tree_node* node_selected;

  //---------------------------
};

#endif
