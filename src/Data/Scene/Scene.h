#ifndef SCENE_GG_H
#define SCENE_GG_H

#include "../../common.h"

class Node_data;
class Param_data;
class Database;
class GPU_data;


class Scene
{
public:
  //ConsScenetor / DesScenetor
  Scene(Node_data* node_data);
  ~Scene();

public:
  void init_set();
  void init_scene();
  void insert_object(Object* object);

private:
  Param_data* param_data;
  Node_data* node_data;
  Database* dataManager;
  GPU_data* gpu_data;

  Set* set_object;
};


#endif
