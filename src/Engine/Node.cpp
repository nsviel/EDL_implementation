#include "Node.h"

#include "Render/Render_node.h"
#include "GUI/Node_gui.h"
#include "Data/Data_node.h"

#include <Window/Window.h>


//Constructor / Destructor
Node::Node(){
  //---------------------------

  this->render_node = new Render_node(this);
  this->data_node = new Data_node(this);
  this->node_gui = new Node_gui(this);

  //---------------------------
}
Node::~Node(){
  //---------------------------

  delete render_node;
  delete node_gui;
  delete data_node;

  //---------------------------
}

void Node::init(Window* window){
  //---------------------------

  render_node->init(window);
  data_node->init();
  node_gui->init(window);
  render_node->loop_start();

  //---------------------------
}
void Node::loop(){
  //---------------------------

  node_gui->loop();

  //---------------------------
}
void Node::exit(){
  //---------------------------

  render_node->exit();

  //---------------------------
}
void Node::reset(){
  //---------------------------

  render_node->reset();
  data_node->reset();

  //---------------------------
}
