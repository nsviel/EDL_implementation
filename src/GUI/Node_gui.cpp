#include "Node_gui.h"

#include "Panel/GUI_left_panel.h"
#include "Operation/GUI_control.h"
#include "Operation/GUI_option.h"
#include "Module/GUI_filemanager.h"

#include "../Node.h"



//Constructor / Destructor
Node_gui::Node_gui(Node* node){
  //---------------------------

  this->node_engine = node->get_node_engine();
  this->node_data = node->get_node_data();
  this->node_load = node->get_node_load();

  this->gui_option = new GUI_option(this);
  this->gui_filemanager = new GUI_filemanager(this);
  this->gui_left_panel = new GUI_left_panel(this);
  this->gui_control = new GUI_control(this);

  //---------------------------
}
Node_gui::~Node_gui(){
  //---------------------------

  delete gui_left_panel;
  delete gui_control;
  delete gui_option;
  delete gui_filemanager;

  //---------------------------
}

//Main function
void Node_gui::loop(){
  //---------------------------

  gui_left_panel->draw_left_panel();
  gui_control->make_control();

  //---------------------------
}
