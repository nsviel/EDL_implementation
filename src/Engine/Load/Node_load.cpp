#include "Node_load.h"

#include "Processing/Loader.h"

#include "../Engine.h"


//Constructor / Destructor
Node_load::Node_load(Engine* engine){
  //---------------------------

  this->node_engine = engine->get_node_engine();
  this->node_data = engine->get_node_data();

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
