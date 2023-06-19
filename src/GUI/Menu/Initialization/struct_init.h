#ifndef STRUCT_INIT_H
#define STRUCT_INIT_H

#include "../../../common.h"


struct Struct_init{
  //---------------------------

  bool remove_old = true;
  float scale = 1;

  vector<string> accepted_format;
  vector<string> vec_path_folder;
  vector<string> vec_path_file;

  //---------------------------
};

#endif
