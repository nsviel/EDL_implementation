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

  //---------------------------
}
Scene::~Scene(){}

void Scene::init_scene(){
  list<Set*>* list_data = dataManager->get_list_data();
  //---------------------------

  //Load init object
  vector<string> vec_path;
  vec_path.push_back(param_data->path_initial_object);
  //vec_path.push_back("../media/bunny.ply");
  vector<Object*> vec_obj = loaderManager->load_objects(vec_path);

  //Add into database
  Set* set = new Set("Cloud");
  for(int i=0; i<vec_obj.size(); i++){
    set->list_obj.push_back(vec_obj[i]);
  }
  list_data->push_back(set);

  //---------------------------
}
