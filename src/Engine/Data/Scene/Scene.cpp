#include "Scene.h"
#include "Database.h"

#include "../Node_data.h"
#include "../Param_data.h"

#include "../../Node.h"
#include "../../Load/Node_load.h"
#include "../../Load/Processing/Loader.h"
#include "../../Core/Node_engine.h"
#include "../../Core/GPU/GPU_data.h"
#include "../../Operation/Transformation/Attribut.h"


//ConsScenetor / DesScenetor
Scene::Scene(Node_data* node_data){
  //---------------------------

  Node_engine* node_engine = node_data->get_node_engine();
  this->node_data = node_data;
  this->param_data = node_data->get_param_data();
  this->dataManager = node_data->get_dataManager();
  this->gpu_data = node_engine->get_gpu_data();
  this->attributManager = new Attribut();

  this->ID_obj = 0;

  //---------------------------
}
Scene::~Scene(){}

//Scene function
void Scene::init_set(){
  list<Set*>* list_data = dataManager->get_list_data_scene();
  //---------------------------

  //Glyph set
  this->set_glyph = new Set("Glyph");
  list_data->push_back(set_glyph);

  //Scene set
  this->set_scene = new Set("Scene");
  list_data->push_back(set_scene);

  //---------------------------
}
void Scene::init_scene(){
  Node* node = node_data->get_node();
  Node_load* node_load = node->get_node_load();
  Loader* loaderManager = node_load->get_loaderManager();
  //---------------------------

  //Load init object
  vector<string> vec_path;
  vec_path.push_back(param_data->path_initial_object);
  vector<Object*> vec_obj = loaderManager->load_objects(vec_path);

  //---------------------------
}
void Scene::reset_scene(){
  //---------------------------

  for(int i=0; i<set_scene->list_obj.size(); i++){
    Object* object = *next(set_scene->list_obj.begin(),i);
    object->reset();
  }

  //---------------------------
}

//Insertion / deletion
void Scene::insert_glyph_object(Object* object){
  //---------------------------

  object->ID = ID_obj++;
  object->is_suppressible = false;
  gpu_data->insert_glyph_in_engine(object);
  set_glyph->list_obj.push_back(object);
  set_glyph->selected_obj = object;
  set_glyph->nb_object++;

  //---------------------------
}
void Scene::insert_scene_object(Object* object){
  //---------------------------

  //Set new object functions
  object->ID = ID_obj++;
  gpu_data->insert_object_in_engine(object);
  attributManager->compute_MinMax(object);

  //Insert it into database
  set_scene->list_obj.push_back(object);
  set_scene->selected_obj = object;
  set_scene->nb_object++;

  //---------------------------
}
void Scene::delete_scene_object(Object* object){
  //---------------------------

  //Delete it from database and engine
  for(int i=0; i<set_scene->list_obj.size(); i++){
    Object* object_list = *next(set_scene->list_obj.begin(),i);
    if(object->ID == object_list->ID){
      set_scene->list_obj.remove(object);
      gpu_data->remove_object_in_engine(object);
      set_scene->nb_object--;
    }
  }

  //---------------------------
}
void Scene::empty_scene_set(){
  //---------------------------

  for(int i=0; i<set_scene->list_obj.size(); i++){
    Object* object = *next(set_scene->list_obj.begin(),i);

    set_scene->list_obj.remove(object);
    gpu_data->remove_object_in_engine(object);
    set_scene->nb_object--;
  }

  //---------------------------
}
