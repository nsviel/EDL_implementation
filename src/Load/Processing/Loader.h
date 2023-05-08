#ifndef LOADER_H
#define LOADER_H

#include "../../common.h"

class Node;
class GPU_data;
class PLY_importer;
class Format;


class Loader
{
public:
  //Constructor / Destructor
  Loader(Node* node);
  ~Loader();

public:
  //Main functions
  Cloud* load_cloud(string path);
  Object* load_object(string path);

  //Subfunctions
  bool is_file_exist(std::string path);
  void transfert_data(Object* object, Data_file* data);

private:
  Format* formatManager;
  GPU_data* gpu_data;
  PLY_importer* plyManager;
};

#endif
