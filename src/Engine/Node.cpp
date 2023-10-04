#include "Node.h"

#include "Core/Node_core.h"
#include "GUI/Node_gui.h"
#include "Data/Data_node.h"


//Constructor / Destructor
Node::Node(){
  //---------------------------

  this->node_core = new Node_core(this);
  this->data_node = new Data_node(this);
  this->node_gui = new Node_gui(this);

  //---------------------------
}
Node::~Node(){
  //---------------------------

  delete node_core;
  delete node_gui;
  delete data_node;

  //---------------------------
}

void Node::init(){
  //---------------------------

  node_core->init();
  data_node->init();
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
  data_node->reset();

  //---------------------------
}
