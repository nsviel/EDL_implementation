#ifndef NODE_SCENE_H
#define NODE_SCENE_H

#include "../common.h"

class Node_core;
class Node;
class Scene;
class Param_data;
class Database;
class Glyphs;
class Control;
class Loader;


class Node_data
{
public:
  //Constructor / Destructor
  Node_data(Node* node);
  ~Node_data();

public:
  void init();
  void reset();

  inline Node* get_node(){return node;}
  inline Node_core* get_node_core(){return node_core;}

  inline Param_data* get_param_data(){return param_data;}
  inline Scene* get_sceneManager(){return sceneManager;}
  inline Database* get_dataManager(){return dataManager;}
  inline Loader* get_loaderManager(){return loaderManager;}
  inline Control* get_controlManager(){return controlManager;}

private:
  Node* node;
  Node_core* node_core;

  Param_data* param_data;
  Scene* sceneManager;
  Database* dataManager;
  Glyphs* glyphManager;
  Control* controlManager;
  Loader* loaderManager;
};

#endif
