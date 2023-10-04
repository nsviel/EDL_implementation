#ifndef NODE_SCENE_H
#define NODE_SCENE_H

#include "../common.h"

class Node_core;
class Node_load;

class Node;
class Scene;
class Param_data;
class Database;
class Glyphs;
class Control;


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
  inline Node_load* get_node_load(){return node_load;}

  inline Param_data* get_param_data(){return param_data;}
  inline Scene* get_sceneManager(){return sceneManager;}
  inline Database* get_dataManager(){return dataManager;}
  inline Control* get_controlManager(){return controlManager;}

private:
  Node* node;
  Node_core* node_core;
  Node_load* node_load;

  Param_data* param_data;
  Scene* sceneManager;
  Database* dataManager;
  Glyphs* glyphManager;
  Control* controlManager;
};

#endif
