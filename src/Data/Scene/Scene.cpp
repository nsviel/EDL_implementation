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

  this->node_data = node_data;
  this->param_data = node_data->get_param_data();
  this->dataManager = node_data->get_dataManager();

  //---------------------------
}
Scene::~Scene(){}

void Scene::init_scene(){
  Node* node = node_data->get_node();
  Node_load* node_load = node->get_node_load();
  Loader* loaderManager = node_load->get_loaderManager();
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
