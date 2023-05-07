#ifndef LOADER_H
#define LOADER_H

#include "../../common.h"

class Node;
class GPU_data;
class PLY_importer;


class Loader
{
public:
  //Constructor / Destructor
  Loader(Node* node);
  ~Loader();

public:
  //Main functions
  Cloud* load_cloud(string path);
  Object* load_model();

  //Subfunctions
  bool is_file_exist(std::string path);

private:
  GPU_data* gpu_data;
  PLY_importer* plyManager;
};

#endif
