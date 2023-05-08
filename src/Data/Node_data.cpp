#include "Node_data.h"
#include "Param_data.h"
#include "Scene/Scene.h"
#include "Data.h"

#include "../Load/Node_load.h"
#include "../Node.h"


//Constructor / Destructor
Node_data::Node_data(Node* node){
  //---------------------------

  this->node_load = node->get_node_load();
  this->param_data = new Param_data();
  this->sceneManager = new Scene(this);
  this->dataManager = new Data(this);

  //---------------------------
}
Node_data::~Node_data(){
  //---------------------------

  delete param_data;
  delete sceneManager;
  delete dataManager;

  //---------------------------
}

void Node_data::init(){
  //---------------------------

  sceneManager->init_scene();

  //---------------------------
}
