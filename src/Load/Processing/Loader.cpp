#include "Loader.h"
#include "Format.h"

#include "../Node_load.h"

#include "../../Specific/File/Directory.h"
#include "../../Specific/File/Zenity.h"
#include "../../Data/Node_data.h"
#include "../../Data/Scene/Scene.h"


//Constructor / Destructor
Loader::Loader(Node_load* node_load){
  //---------------------------

  Node_data* node_data = node_load->get_node_data();
  this->sceneManager = node_data->get_sceneManager();
  this->formatManager = new Format();

  this->ID = 0;
  this->path_current_dir = "";

  //---------------------------
}
Loader::~Loader(){
  //---------------------------

  delete formatManager;

  //---------------------------
}

//Main functions
Object* Loader::load_object(string path){
  //---------------------------

  //Create new object
  Object* object = new Object();
  object->path_file = path;
  object->path_text = "../media/viking_room.png";
  object->draw_type_name = "point";
  object->has_texture = true;
  object->ID = ID++;

  //Retrieve data and insert into engine
  Data_file* data = formatManager->get_data_from_file(path);
  this->transfert_data(object, data);
  sceneManager->insert_scene_object(object);

  //---------------------------
  return object;
}
vector<Object*> Loader::load_objects(vector<string> path){
  vector<Object*> vec_obj;
  //---------------------------

  for(int i=0; i<path.size(); i++){
    Object* object = load_object(path[i]);
    vec_obj.push_back(object);
  }

  //---------------------------
  return vec_obj;
}
void Loader::load_by_zenity(){
  //---------------------------

  //Select files to load
  vector<string> path_vec = zenity_file_vec("Load", path_current_dir);

  //Add object in engine
  this->load_objects(path_vec);

  //---------------------------
}

//Subfunctions
void Loader::transfert_data(Object* object, Data_file* data){
  //---------------------------

  object->name = data->name;
  object->nb_point = data->xyz.size();

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
