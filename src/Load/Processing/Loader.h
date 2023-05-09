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
  Object* load_object(string path);
  vector<Object*> load_objects(vector<string> path);
  void load_object_zenity();

  //Subfunctions
  void transfert_data(Object* object, Data_file* data);

private:
  Format* formatManager;
  GPU_data* gpu_data;
  PLY_importer* plyManager;

  string path_current_dir;
  int ID;
};

#endif
