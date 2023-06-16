#ifndef LOADER_H
#define LOADER_H

#include "../../common.h"

class Node_load;
class Format;
class Scene;


class Loader
{
public:
  //Constructor / Destructor
  Loader(Node_load* node_load);
  ~Loader();

public:
  //Main functions
  Object* load_object(string path);
  vector<Object*> load_objects(vector<string> path);
  void load_by_zenity();

  //Subfunctions
  void transfert_data(Object* object, Data_file* data);

private:
  Format* formatManager;
  Scene* sceneManager;

  string path_current_dir;
  int ID;
};

#endif
