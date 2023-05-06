#include "Node_gui.h"

#include "Panel/GUI_left_panel.h"
#include "Operation/GUI_control.h"

#include "../Node.h"



//Constructor / Destructor
Node_gui::Node_gui(Node* node){
  //---------------------------

  this->gui_left_panel = new GUI_left_panel(node);
  this->gui_control = new GUI_control(node);

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
  gui_control->make_control();

  //---------------------------
}
