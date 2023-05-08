#include "Node_load.h"

#include "Processing/Loader.h"

#include "../Node.h"


//Constructor / Destructor
Node_load::Node_load(Node* node){
  //---------------------------

  this->loaderManager = new Loader(node);

  //---------------------------
}
Node_load::~Node_load(){
  //---------------------------

  delete loaderManager;

  //---------------------------
}

//Main function
void Node_load::loop(){
  //---------------------------


  //---------------------------
}
