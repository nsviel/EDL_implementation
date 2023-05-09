#include "Node_load.h"

#include "Processing/Loader.h"

#include "../Node.h"


//Constructor / Destructor
Node_load::Node_load(Node* node){
  //---------------------------

  this->node_engine = node->get_node_engine();
  this->node_data = node->get_node_data();

  this->loaderManager = new Loader(this);

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
