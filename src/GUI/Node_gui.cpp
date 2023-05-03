#include "Node_gui.h"

#include "../Engine/Node_engine.h"
#include "GUI.h"


//Constructor / Destructor
Node_gui::Node_gui(Node_engine* node_engine){
  //---------------------------

  this->node_engine = node_engine;
  this->guiManager = new GUI(node_engine);

  //---------------------------
}
Node_gui::~Node_gui(){
  //---------------------------

  delete guiManager;

  //---------------------------
}

//Main function
