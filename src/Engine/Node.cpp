#include "Node.h"

#include "Render/Render_node.h"
#include "GUI/Node_gui.h"
#include "Data/Data_node.h"

#include <Window/Window.h>


//Constructor / Destructor
Node::Node(Window* window){
  //---------------------------

  this->window = window;
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

void Node::init(){
  //---------------------------

  render_node->init();
  data_node->init();
  node_gui->init();


  //---------------------------
}
void Node::loop(){
  //---------------------------

  

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
