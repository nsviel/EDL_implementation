#include "Node.h"

#include "Engine/Node_engine.h"
#include "Load/Node_load.h"
#include "GUI/Node_gui.h"
#include "Data/Node_data.h"
#include "Operation/Node_operation.h"


//Constructor / Destructor
Node::Node(){
  //---------------------------

  this->node_ope = new Node_operation(this);
  this->node_engine = new Node_engine(this);
  this->node_data = new Node_data(this);
  this->node_load = new Node_load(this);
  this->node_gui = new Node_gui(this);

  //---------------------------
}
Node::~Node(){
  //---------------------------

  delete node_engine;
  delete node_load;
  delete node_gui;
  delete node_data;

  //---------------------------
}

void Node::init(){
  //---------------------------

  node_engine->init();
  node_data->init();
  node_engine->loop_start();

  //---------------------------
}
void Node::loop(){
  //---------------------------

  node_gui->loop();

  //---------------------------
}
void Node::exit(){
  //---------------------------

  node_engine->exit();

  //---------------------------
}
