#include "PLY_exporter.h"

#include "../../../Specific/Function/fct_math.h"


//Constructor / Destructor
PLY_exporter::PLY_exporter(){}
PLY_exporter::~PLY_exporter(){}

//Main exporter functions
bool PLY_exporter::export_cloud(Cloud* cloud, string path_dir, string ply_format){
  string filePath = path_dir + cloud->name + ".tmp";
  string filePath_end = path_dir + cloud->name + ".ply";
  //---------------------------


  //---------------------------
  return true;
}
