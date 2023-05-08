#include "Scene.h"

#include "../Node_data.h"
#include "../Param_data.h"

//#include "../Glyph/Object.h"
//#include "../../Engine/GPU/GPU_data.h"

#include "../../Node.h"
#include "../../Load/Node_load.h"
#include "../../Load/Processing/Loader.h"


//ConsScenetor / DesScenetor
Scene::Scene(Node_data* node_data){
  //---------------------------

  Node_load* node_load = node_data->get_node_load();
  this->loaderManager = node_load->get_loaderManager();
  this->param_data = node_data->get_param_data();

  //this->objectManager = new Object();
  //this->gpuManager = new GPU_data();

  //---------------------------
}
Scene::~Scene(){}

void Scene::init_scene(){
  //---------------------------

  loaderManager->load_object(param_data->path_initial_object);

  //---------------------------
}


/*
//Remove functions
void Scene::remove_collection(Collection* collection){
  std::list<Collection*>* list_collection = data->get_list_col_object();
  //---------------------------

  if(list_collection->size() != 0){
    int ID_order = collection->ID_col_order;
    string name =  collection->name;
    //---------------------------

    //Delete subsets
    collection->obj_remove_all();

    //Delete collection
    delete collection;
    collection = nullptr;

    //Delete collection iterator in list
    list<Collection*>::iterator it = next(list_collection->begin(), ID_order);
    list_collection->erase(it);

    data->update_ID_order();
    data->set_selected_collection(ID_order);

    //---------------------------
    string log = "Collection "+ name +" removed";
    console.AddLog("#", log);
  }

  //If collection list empty
  if(list_collection->size() == 0){
    objectManager->reset_scene_object();
  }

  //---------------------------
}
void Scene::remove_collection_all(){
  std::list<Collection*>* list_collection = data->get_list_col_object();
  //---------------------------

  while(list_collection->size() != 0){
    Collection* collection = *list_collection->begin();
    this->remove_collection(collection);
  }

  //---------------------------
}

//Reset functions
void Scene::reset_collection(Collection* collection){
  //---------------------------

  collection->reset();

  //Update
  for(int i=0; i<collection->list_obj.size(); i++){
    this->update_MinMax(collection->get_obj(i));
    this->update_buffer_location(collection->get_obj(i));
    this->update_buffer_color(collection->get_obj(i));
  }

  //---------------------------
  this->update_glyph(collection);
}
void Scene::reset_collection_all(){
  std::list<Collection*>* list_collection = data->get_list_col_object();
  //---------------------------

  //Reset all collections
  for(int i=0; i<list_collection->size(); i++){
    Collection* collection = *next(list_collection->begin(),i);
    this->reset_collection(collection);
  }

  Collection* col = data->get_selected_collection();
  this->update_glyph(col);

  //---------------------------
  console.AddLog("#", "Reset scene...");
}

//Update collection
void Scene::update_collection_location(Collection* collection){
  //---------------------------

  for(int i=0; i<collection->nb_obj; i++){
    Object_* object = collection->get_obj(i);
    this->update_buffer_location(object);
  }

  //---------------------------
}
void Scene::update_collection_color(Collection* collection){
  //---------------------------

  for(int i=0; i<collection->nb_obj; i++){
    Object_* object = collection->get_obj(i);
    this->update_buffer_color(object);
  }

  //---------------------------
}
void Scene::update_collection_MinMax(Collection* collection){
  //---------------------------

  for(int i=0; i<collection->nb_obj; i++){
    Object_* object = collection->get_obj(i);
    this->update_MinMax(object);
  }

  //---------------------------
}

//Update object
void Scene::update_buffer_location(Object_* object){
  //---------------------------

  gpuManager->update_buffer_location(object);

  //---------------------------
}
void Scene::update_buffer_color(Object_* object){
  //---------------------------

  gpuManager->update_buffer_color(object);

  //---------------------------
}
void Scene::update_MinMax(Object_* object){
  vector<vec3>& XYZ = object->xyz;
  vec3 centroid = vec3(0, 0, 0);
  vec3 min = XYZ[0];
  vec3 max = XYZ[0];
  //---------------------------

  for(int i=0; i<XYZ.size(); i++){
    for(int j=0; j<3; j++){
      if ( XYZ[i][j] <= min[j] ) min[j] = XYZ[i][j];
      if ( XYZ[i][j] >= max[j] ) max[j] = XYZ[i][j];
      centroid[j] += XYZ[i][j];
    }
  }

  for(int j=0;j<3;j++){
    centroid[j] /= XYZ.size();
  }

  //---------------------------
  object->min = min;
  object->max = max;
  object->COM = centroid;
}

//Update collection function
void Scene::update_glyph(Collection* collection){
  if(collection == nullptr) return;
  if(collection->obj_type != "cloud") return;
  //---------------------------

  for(int i=0; i<collection->list_obj.size(); i++){
    Cloud* cloud = (Cloud*)collection->get_obj(i);
    this->update_MinMax(cloud);
    objectManager->update_glyph_cloud(cloud);
  }

  //---------------------------
}
void Scene::update_MinMax_col(Collection* collection){
  vec3 min_cloud = vec3(100, 100, 100);
  vec3 max_cloud = vec3(-100, -100, -100);
  //---------------------------

  for(int i=0; i<collection->list_obj.size(); i++){
    Cloud* cloud = (Cloud*)*next(collection->list_obj.begin(), i);
    this->update_MinMax(cloud);

    //Collection
    for(int j=0; j<3; j++){
      if ( min_cloud[j] > cloud->min[j] ) min_cloud[j] = cloud->min[j];
      if ( max_cloud[j] < cloud->max[j] ) max_cloud[j] = cloud->max[j];
    }
  }

  //---------------------------
  collection->min = min_cloud;
  collection->max = max_cloud;
}
*/
