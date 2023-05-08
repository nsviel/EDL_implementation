#include "Format.h"

#include "../Format/PLY/PLY_importer.h"


//Constructor / Destructor
Format::Format(){
  //---------------------------

  this->ply_import = new PLY_importer();

  //---------------------------
}
Format::~Format(){
  //---------------------------

  delete ply_import;

  //---------------------------
}

//Main functions
