#include "Node_gui.h"
#include "GUI_param.h"

#include "Panel/GUI_panel.h"
#include "Editor/GUI_editor_text.h"
#include "Panel/GUI_engine.h"
#include "Menu/GUI_menubar.h"
#include "Menu/GUI_option.h"
#include "Menu/GUI_init.h"
#include "Control/GUI_control.h"
#include "Control/GUI_profiling.h"
#include "Engine/GUI_shader.h"
#include "Panel/GUI_object.h"
#include "Window/GUI_windows.h"
#include "Style/GUI_style.h"
#include "Control/Control.h"

#include "../Node.h"

#include <Window/Window.h>


//Constructor / Destructor
Node_gui::Node_gui(Node* node){
  //---------------------------

  this->node = node;
  this->window = window;
  this->render_node = node->get_render_node();
  this->data_node = node->get_data_node();

  this->controlManager = new Control(this);
  this->gui_param = new GUI_param();
  this->gui_profiling = new GUI_profiling(this);
  this->gui_shader = new GUI_shader(this);
  this->gui_option = new GUI_option(this);
  this->gui_object = new GUI_object(this);
  this->gui_init = new GUI_init(this);
  this->gui_menubar = new GUI_menubar(this);
  this->gui_editor_text = new GUI_editor_text(this);
  this->gui_control = new GUI_control(this);
  this->gui_engine = new GUI_engine(this);
  this->gui_panel = new GUI_panel(this);
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
  delete gui_object;
  delete gui_profiling;

  //---------------------------
}

//Main function
void Node_gui::init(){
  //---------------------------

  gui_style->gui_style();
  gui_panel->set_initial_panel_focus();

  //---------------------------
}
void Node_gui::loop(){
  //---------------------------

  gui_panel->draw_panels();
  gui_windows->draw_windows();

  //---------------------------
}
