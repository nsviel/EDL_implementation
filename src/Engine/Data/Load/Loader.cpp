#include "Loader.h"
#include "Format.h"
#include "../Data_node.h"
#include "../Scene/Scene.h"


//Constructor / Destructor
Loader::Loader(Data_node* data_node){
  //---------------------------

  this->sceneManager = data_node->get_sceneManager();
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
Object* Loader::load_object(std::string path){
  //---------------------------

  if(is_file_exist(path) == false){
    cout<<"[error] File doesn't exists at "<<path<<endl;
    return nullptr;
  }

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
std::vector<Object*> Loader::load_objects(std::vector<std::string> path){
  std::vector<Object*> vec_obj;
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
  std::vector<std::string> path_vec = zenity_file_vec("Load", path_current_dir);

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