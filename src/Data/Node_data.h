#ifndef NODE_SCENE_H
#define NODE_SCENE_H

#include "../common.h"

class Node_load;
class Node;
class Scene;
class Param_data;
class Database;


class Node_data
{
public:
  //Constructor / Destructor
  Node_data(Node* node);
  ~Node_data();

public:
  void init();

  inline Node_load* get_node_load(){return node_load;}
  inline Param_data* get_param_data(){return param_data;}
  inline Scene* get_sceneManager(){return sceneManager;}
  inline Database* get_dataManager(){return dataManager;}

private:
  Node_load* node_load;
  Param_data* param_data;
  Scene* sceneManager;
  Database* dataManager;
};

#endif
