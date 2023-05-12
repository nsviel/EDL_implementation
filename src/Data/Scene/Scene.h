#ifndef SCENE_GG_H
#define SCENE_GG_H

#include "../../common.h"

class Node_data;
class Param_data;
class Database;
class GPU_data;
class Attribut;


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
  void insert_glyph(Object* object);
  void reset_scene();

  inline Set* get_set_object(){return set_object;}
  inline Set* get_set_glyph(){return set_glyph;}

private:
  Param_data* param_data;
  Node_data* node_data;
  Database* dataManager;
  GPU_data* gpu_data;
  Attribut* attributManager;

  int ID_obj;
  Set* set_object;
  Set* set_glyph;
};


#endif
