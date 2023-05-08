#include "Scene.h"
#include "Database.h"

#include "../Node_data.h"
#include "../Param_data.h"

#include "../../Node.h"
#include "../../Load/Node_load.h"
#include "../../Load/Processing/Loader.h"


//ConsScenetor / DesScenetor
Scene::Scene(Node_data* node_data){
  //---------------------------

  Node_load* node_load = node_data->get_node_load();
  this->loaderManager = node_load->get_loaderManager();
  this->param_data = node_data->get_param_data();
  this->dataManager = node_data->get_dataManager();

  //this->objectManager = new Object();
  //this->gpuManager = new GPU_data();

  //---------------------------
}
Scene::~Scene(){}

void Scene::init_scene(){
  list<Set*>* list_data = dataManager->get_list_data();
  //---------------------------

  //Load init object
  Object* object = loaderManager->load_object(param_data->path_initial_object);

  //Add into database
  Set* set = new Set("Init_object");
  set->list_obj.push_back(object);
  list_data->push_back(set);

  set = new Set("dddd");
  set->list_obj.push_back(object);
  list_data->push_back(set);

  set = new Set("fffff");
  set->list_obj.push_back(object);
  list_data->push_back(set);

  //---------------------------
}
