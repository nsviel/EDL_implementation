#include "Loader.h"
#include "Format.h"

#include "../Format/PLY/PLY_importer.h"

#include "../../Specific/File/Directory.h"
#include "../../Specific/File/Zenity.h"
#include "../../Engine/Node_engine.h"
#include "../../Engine/GPU/GPU_data.h"
#include "../../Node.h"

#include "../../../extern/tiny_obj_loader.h"


//Constructor / Destructor
Loader::Loader(Node* node){
  //---------------------------

  Node_engine* node_engine = node->get_node_engine();
  this->gpu_data = node_engine->get_gpu_data();
  this->plyManager = new PLY_importer();
  this->formatManager = new Format();

  this->ID = 0;
  this->path_current_dir = "";

  //---------------------------
}
Loader::~Loader(){
  //---------------------------

  delete plyManager;

  //---------------------------
}

//Main functions
Object* Loader::load_object(string path){
  //---------------------------

  //DOIT se relier à scene et pas a GPU_data
  //scene doit gérer les IDs et l'envoie à gpu_data

  Object* object = new Object();
  object->path_file = path;
  object->path_text = "../media/viking_room.png";
  object->draw_type_name = "point";
  object->has_texture = true;
  object->ID = ID++;

  Data_file* data = formatManager->get_data_from_file(path);
  this->transfert_data(object, data);
  gpu_data->insert_object_in_engine(object);
  gpu_data->update_descriptor_set();

  //---------------------------
  return object;
}
vector<Object*> Loader::load_objects(vector<string> path){
  vector<Object*> vec_obj;
  //---------------------------

  for(int i=0; i<path.size(); i++){
    Object* object = new Object();
    object->path_file = path[i];
    object->path_text = "../media/viking_room.png";
    object->draw_type_name = "point";
    object->has_texture = true;
    object->ID = ID++;

    Data_file* data = formatManager->get_data_from_file(path[i]);
    this->transfert_data(object, data);
    gpu_data->insert_object_in_engine(object);
    vec_obj.push_back(object);
  }

  gpu_data->update_descriptor_set();

  //---------------------------
  return vec_obj;
}
void Loader::load_object_zenity(){
  //---------------------------

  //Select files to load
  vector<string> path_vec = zenity_file_vec("Cloud loading", path_current_dir);
  if(path_vec.size() == 0){
    return;
  }

  //Create new object
  Object* object = new Object();
  object->path_file = path_vec[0];
  object->draw_type_name = "point";
  object->has_texture = false;
  object->ID = ID++;

  //Add object in engine
  for(int i=0; i<path_vec.size(); i++){
    Data_file* data = formatManager->get_data_from_file(path_vec[0]);
    this->transfert_data(object, data);
    gpu_data->insert_object_in_engine(object);
  }

  //---------------------------
}

//Subfunctions
void Loader::transfert_data(Object* object, Data_file* data){
  //---------------------------

  object->name = data->name;

  object->xyz = data->xyz;
  object->rgb = data->rgb;
  object->uv = data->uv;

  if(object->rgb.size() == 0){
    for(int i=0; i<data->xyz.size(); i++){
      object->rgb.push_back(vec4(1,1,1,1));
    }
  }

  //Delete raw data
  delete data;

  //---------------------------
}
