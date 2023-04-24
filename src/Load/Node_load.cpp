#include "Node_load.h"

#include "Loader.h"


//Constructor / Destructor
Node_load::Node_load(Node_engine* Node_engine){
  //---------------------------

  this->loaderManager = new Loader();

  //---------------------------
}
Node_load::~Node_load(){
  //---------------------------

  delete loaderManager;

  //---------------------------
}

//Main function
