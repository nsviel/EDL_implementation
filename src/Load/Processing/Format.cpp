#include "Format.h"

#include "../Format/PLY/PLY_importer.h"
#include "../Format/File_obj.h"


//Constructor / Destructor
Format::Format(){
  //---------------------------

  this->ply_import = new PLY_importer();
  this->obj_import = new File_obj();

  //---------------------------
}
Format::~Format(){
  //---------------------------

  delete ply_import;
  delete obj_import;

  //---------------------------
}

//Main functions
Data_file* Format::get_data_from_file(string path){
  Data_file* data;
  //---------------------------

  string format = get_format_from_path(path);
  if     (format == "ply"){
    data = ply_import->Loader(path);
  }
  else if(format == "obj"){
    data = obj_import->Loader(path);
  }

  //---------------------------
  return data;
}
