#include "Node.h"

#include "Render/Core_node.h"
#include "GUI/Node_gui.h"
#include "Data/Data_node.h"


//Constructor / Destructor
Node::Node(){
  //---------------------------

  this->core_node = new Core_node(this);
  this->data_node = new Data_node(this);
  this->node_gui = new Node_gui(this);

  //---------------------------
}
Node::~Node(){
  //---------------------------

  delete core_node;
  delete node_gui;
  delete data_node;

  //---------------------------
}

void Node::init(){
  //---------------------------

  core_node->init();
  data_node->init();
  node_gui->init();
  core_node->loop_start();

  //---------------------------
}
void Node::loop(){
  //---------------------------

  node_gui->loop();

  //---------------------------
}
void Node::exit(){
  //---------------------------

  core_node->exit();

  //---------------------------
}
void Node::reset(){
  //---------------------------

  core_node->reset();
  data_node->reset();

  //---------------------------
}
