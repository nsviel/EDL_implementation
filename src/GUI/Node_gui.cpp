#include "Node_gui.h"
#include "GUI_param.h"

#include "Panel/GUI_panel.h"
#include "Panel/GUI_editor.h"
#include "Panel/GUI_engine.h"
#include "Menu/GUI_menubar.h"
#include "Menu/GUI_option.h"
#include "Menu/GUI_init.h"
#include "Control/GUI_control.h"
#include "Control/GUI_profiling.h"
#include "Engine/GUI_shader.h"
#include "Panel/GUI_filemanager.h"
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
  this->gui_profiling = new GUI_profiling(this);
  this->gui_shader = new GUI_shader(this);
  this->gui_option = new GUI_option(this);
  this->gui_filemanager = new GUI_filemanager(this);
  this->gui_init = new GUI_init(this);
  this->gui_menubar = new GUI_menubar(this);
  this->gui_editor = new GUI_editor(this);
  this->gui_engine = new GUI_engine(this);
  this->gui_panel = new GUI_panel(this);
  this->gui_control = new GUI_control(this);
  this->gui_windows = new GUI_windows(this);
  this->gui_style = new GUI_style(this);

  //---------------------------
}
Node_gui::~Node_gui(){
  //---------------------------

  delete gui_param;
  delete gui_panel;
  delete gui_control;
  delete gui_option;
  delete gui_filemanager;
  delete gui_profiling;

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

  gui_panel->draw_panels();
  gui_control->make_control();
  gui_windows->draw_windows();

  //---------------------------
}
