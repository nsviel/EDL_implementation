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

  Object* object = new Object();
  object->path_file = path;
  object->path_text = "../media/viking_room.png";
  object->draw_type_name = "point";
  object->has_texture = true;
  object->ID = ID++;

  Data_file* data = formatManager->get_data_from_file(path);
  this->transfert_data(object, data);
  gpu_data->insert_object_in_engine(object);

  //---------------------------
  return object;
}
void Loader::load_object_zenity(){
  //---------------------------

  //select files
  vector<string> path_vec = zenity_file_vec("Cloud loading", path_current_dir);

  Object* object = new Object();
  object->path_file = path_vec[0];
  object->draw_type_name = "point";
  object->has_texture = false;
  object->ID = ID++;

  //Load 1 collection by cloud
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
