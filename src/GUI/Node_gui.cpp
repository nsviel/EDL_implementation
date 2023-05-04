#include "Node_gui.h"

#include "GUI_left_panel.h"
#include "GUI_control.h"

#include "../Engine/Node_engine.h"



//Constructor / Destructor
Node_gui::Node_gui(Node_engine* node_engine){
  //---------------------------

  this->node_engine = node_engine;
  this->gui_left_panel = new GUI_left_panel(node_engine);
  this->gui_control = new GUI_control(node_engine);

  //---------------------------
}
Node_gui::~Node_gui(){
  //---------------------------

  delete gui_left_panel;

  //---------------------------
}

//Main function
void Node_gui::loop(){
  //---------------------------

  gui_left_panel->draw_left_panel();

  //---------------------------
}
