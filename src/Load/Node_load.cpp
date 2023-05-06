#include "Node_load.h"

#include "Loader.h"

#include "../Node.h"


//Constructor / Destructor
Node_load::Node_load(Node* node){
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
