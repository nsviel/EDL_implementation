#ifndef SCENE_GG_H
#define SCENE_GG_H

#include "../../common.h"

class Node_data;
class Object;
class GPU_data;
class Loader;
class Param_data;


class Scene
{
public:
  //ConsScenetor / DesScenetor
  Scene(Node_data* node_data);
  ~Scene();

public:
  void init_scene();

  //Remove functions
  void remove_collection(Set* set);
  void remove_collection_all();

  //Reset functions
  void reset_collection(Set* set);
  void reset_collection_all();

  //Update set
  void update_collection_location(Set* set);
  void update_collection_color(Set* set);
  void update_collection_MinMax(Set* set);

  //Update object function
  void update_buffer_location(Object* object);
  void update_buffer_color(Object* object);
  void update_MinMax(Object* object);

  //Update set function
  void update_glyph(Set* set);
  void update_MinMax_col(Set* set);

/*  inline int get_nb_cloud(){return data->get_list_col_object()->size();}
  inline list<Set*>* get_list_col_object(){return data->get_list_col_object();}
  inline Set* get_selected_collection(){return data->get_selected_collection();}
  inline Cloud* get_selected_cloud(){Set* col = data->get_selected_collection();return (Cloud*)col->selected_obj;}
  inline void set_selected_collection(Set* col){}
  inline bool get_is_list_empty(){return data->get_list_col_object()->empty();}
*/
private:
  Object* objectManager;
  Param_data* param_data;
  Loader* loaderManager;
  GPU_data* gpuManager;
  Data_file* data;
};

#endif
