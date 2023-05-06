#include "Node.h"

#include "Engine/Node_engine.h"
#include "Load/Node_load.h"
#include "GUI/Node_gui.h"
#include "Data/Node_data.h"


//Constructor / Destructor
Node::Node(){
  //---------------------------

  this->node_engine = new Node_engine(this);
  this->node_load = new Node_load(this);
  this->node_gui = new Node_gui(this);
  this->node_data = new Node_data(this);

  //---------------------------
}
Node::~Node(){
  //---------------------------

  delete node_engine;
  delete node_load;
  delete node_gui;

  //---------------------------
}

void Node::init(){
  //---------------------------

  node_engine->init();

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
