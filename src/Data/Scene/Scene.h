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
  //Scene function
  void init_set();
  void init_scene();
  void reset_scene();

  //Insertion / deletion
  void insert_glyph_object(Object* object);
  void insert_scene_object(Object* object);
  void delete_scene_object(Object* object);
  void empty_scene_set();
  
  inline Set* get_set_scene(){return set_scene;}
  inline Set* get_set_glyph(){return set_glyph;}
  inline Object* get_selected_object(){return set_scene->selected_obj;}

private:
  Param_data* param_data;
  Node_data* node_data;
  Database* dataManager;
  GPU_data* gpu_data;
  Attribut* attributManager;

  int ID_obj;
  Set* set_scene;
  Set* set_glyph;
};


#endif
