#include "Loader.h"
#include "Format.h"

#include "../Format/PLY/PLY_importer.h"

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

  //---------------------------
}
Loader::~Loader(){
  //---------------------------

  delete plyManager;

  //---------------------------
}

//Main functions
Cloud* Loader::load_cloud(string path){
  Cloud* cloud = new Cloud();
  //---------------------------

  //Check file existence
  if(is_file_exist(path) == false){
    string log = "File doesn't exists: "+ path;
  }

  //Load file data
  Data* data = plyManager->Loader(path);

  cloud->name = data->name;
  cloud->xyz = data->xyz;
  cloud->rgb = data->rgb;

  //Delete raw data
  delete data;

  //---------------------------
  return cloud;
}
Object* Loader::load_object(string path){
  //---------------------------

  Object* object = new Object();
  object->path_file = path;
  object->path_text = "../media/viking_room.png";
  object->draw_type_name = "point";
  object->has_texture = true;

  Data* data = formatManager->get_data_from_file(path);

  object->xyz = data->xyz;
  object->rgb = data->rgb;
  object->uv = data->uv;

  if(object->rgb.size() == 0){
    for(int i=0; i<data->xyz.size(); i++){
      object->rgb.push_back(vec4(1,1,1,1));
    }
  }

  gpu_data->insert_object_in_engine(object);

  //---------------------------
  return object;
}

//Subfunctions
bool Loader::is_file_exist(std::string path){
  //---------------------------

  std::ifstream infile(path.c_str());

  //---------------------------
  return infile.good();
}
