#include "Scene.h"
#include "Database.h"

#include "../Node_data.h"
#include "../Param_data.h"

#include "../../Node.h"
#include "../../Load/Node_load.h"
#include "../../Load/Processing/Loader.h"
#include "../../Engine/Node_engine.h"
#include "../../Engine/GPU/GPU_data.h"


//ConsScenetor / DesScenetor
Scene::Scene(Node_data* node_data){
  //---------------------------

  Node_engine* node_engine = node_data->get_node_engine();
  this->node_data = node_data;
  this->param_data = node_data->get_param_data();
  this->dataManager = node_data->get_dataManager();
  this->gpu_data = node_engine->get_gpu_data();

  //---------------------------
}
Scene::~Scene(){}

void Scene::init_set(){
  list<Set*>* list_data = dataManager->get_list_data();
  //---------------------------

  this->set_object = new Set("Object");
  list_data->push_back(set_object);

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
  vec_path.push_back("../media/bunny.ply");
  vec_path.push_back("../media/bunny.ply");
  vector<Object*> vec_obj = loaderManager->load_objects(vec_path);

  //---------------------------
}
void Scene::insert_object(Object* object){
  //---------------------------

  gpu_data->insert_object_in_engine(object);
  set_object->list_obj.push_back(object);
  //gpu_data->update_descriptor_set();

  //---------------------------
}
