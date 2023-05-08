#ifndef NODE_SCENE_H
#define NODE_SCENE_H

#include "../common.h"

class Node_load;
class Node;
class Scene;
class Param_data;
class Data;


class Node_data
{
public:
  //Constructor / Destructor
  Node_data(Node* node);
  ~Node_data();

public:
  void init();

  inline Node_load* get_node_load(){return node_load;}
  inline Scene* get_sceneManager(){return sceneManager;}
  inline Param_data* get_param_data(){return param_data;}

private:
  Node_load* node_load;
  Param_data* param_data;
  Scene* sceneManager;
  Data* dataManager;
};

#endif
