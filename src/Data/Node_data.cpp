#include "Node_data.h"
#include "Param_data.h"
#include "Scene/Scene.h"

#include "../Load/Node_load.h"
#include "../Node.h"


//Constructor / Destructor
Node_data::Node_data(Node* node){
  //---------------------------

  this->node_load = node->get_node_load();
  this->param_data = new Param_data();
  this->sceneManager = new Scene(this);

  //---------------------------
}
Node_data::~Node_data(){
  //---------------------------

  delete sceneManager;

  //---------------------------
}

void Node_data::init(){
  //---------------------------

  sceneManager->init_scene();

  //---------------------------
}
