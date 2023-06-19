#include "Node_gui.h"
#include "GUI_param.h"

#include "Panel/GUI_left_panel.h"
#include "Menu/GUI_menubar.h"
#include "Menu/GUI_option.h"
#include "Menu/Initialization/GUI_init.h"
#include "Control/GUI_control.h"
#include "Control/GUI_time.h"
#include "Engine/GUI_shader.h"
#include "Engine/GUI_device.h"
#include "Data/GUI_filemanager.h"
#include "Window/GUI_windows.h"
#include "Style/GUI_style.h"

#include "../Node.h"



//Constructor / Destructor
Node_gui::Node_gui(Node* node){
  //---------------------------

  this->node_engine = node->get_node_engine();
  this->node_data = node->get_node_data();
  this->node_load = node->get_node_load();

  this->gui_param = new GUI_param();
  this->gui_time = new GUI_time(this);
  this->gui_shader = new GUI_shader(this);
  this->gui_option = new GUI_option(this);
  this->gui_filemanager = new GUI_filemanager(this);
  this->gui_init = new GUI_init(this);
  this->gui_menubar = new GUI_menubar(this);
  this->gui_device = new GUI_device(this);
  this->gui_left_panel = new GUI_left_panel(this);
  this->gui_control = new GUI_control(this);
  this->gui_windows = new GUI_windows(this);
  this->gui_style = new GUI_style(this);

  //---------------------------
}
Node_gui::~Node_gui(){
  //---------------------------

  delete gui_param;
  delete gui_left_panel;
  delete gui_control;
  delete gui_option;
  delete gui_filemanager;
  delete gui_time;

  //---------------------------
}

//Main function
void Node_gui::init(){
  //---------------------------

  gui_style->gui_style();

  //---------------------------
}
void Node_gui::loop(){
  //---------------------------

  gui_left_panel->draw_left_panel();
  gui_control->make_control();
  gui_windows->draw_windows();

  //---------------------------
}
