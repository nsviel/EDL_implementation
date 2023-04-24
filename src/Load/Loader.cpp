#include "Loader.h"

#include "Format/PLY/PLY_importer.h"


//Constructor / Destructor
Loader::Loader(){
  //---------------------------

  this->plyManager = new PLY_importer();

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

//Subfunctions
bool Loader::is_file_exist(std::string path){
  //---------------------------

  std::ifstream infile(path.c_str());

  //---------------------------
  return infile.good();
}
