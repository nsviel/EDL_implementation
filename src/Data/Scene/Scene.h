#ifndef SCENE_GG_H
#define SCENE_GG_H

#include "../../common.h"

class Node_data;
class Param_data;
class Database;


class Scene
{
public:
  //ConsScenetor / DesScenetor
  Scene(Node_data* node_data);
  ~Scene();

public:
  void init_scene();

private:
  Param_data* param_data;
  Node_data* node_data;
  Database* dataManager;
};


#endif
