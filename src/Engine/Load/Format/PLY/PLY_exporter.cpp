#include "PLY_exporter.h"


//Constructor / Destructor
PLY_exporter::PLY_exporter(){}
PLY_exporter::~PLY_exporter(){}

//Main exporter functions
bool PLY_exporter::export_cloud(Object* object, std::string path_dir, std::string ply_format){
  std::string filePath = path_dir + object->name + ".tmp";
  std::string filePath_end = path_dir + object->name + ".ply";
  //---------------------------


  //---------------------------
  return true;
}
