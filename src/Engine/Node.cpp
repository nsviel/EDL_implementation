#include "Node.h"

#include "Core/Node_core.h"
#include "GUI/Node_gui.h"
#include "Data/Node_data.h"


//Constructor / Destructor
Node::Node(){
  //---------------------------

  this->node_core = new Node_core(this);
  this->node_data = new Node_data(this);
  this->node_gui = new Node_gui(this);

  //---------------------------
}
Node::~Node(){
  //---------------------------

  delete node_core;
  delete node_gui;
  delete node_data;

  //---------------------------
}

void Node::init(){
  //---------------------------

  node_core->init();
  node_data->init();
  node_gui->init();
  node_core->loop_start();

  //---------------------------
}
void Node::loop(){
  //---------------------------

  node_gui->loop();

  //---------------------------
}
void Node::exit(){
  //---------------------------

  node_core->exit();

  //---------------------------
}
void Node::reset(){
  //---------------------------

  node_core->reset();
  node_data->reset();

  //---------------------------
}
