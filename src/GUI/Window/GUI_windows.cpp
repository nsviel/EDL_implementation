#include "GUI_windows.h"

#include "WIN_camera.h"
#include "WIN_object.h"
#include "WIN_set.h"

#include <GUI_node.h>
#include "../GUI_param.h"


//Constructor / Destructor
GUI_windows::GUI_windows(GUI_node* gui_node){
  //---------------------------

  this->gui_param = gui_node->get_gui_param();
  this->win_camera = new WIN_camera(gui_node, &gui_param->show_camera, "Camera");
  this->win_object = new WIN_object(gui_node, &gui_param->show_object, "Object");
  this->win_set = new WIN_set(gui_node, &gui_param->show_set, "Set");

  //---------------------------
}
GUI_windows::~GUI_windows(){}

//Main function
void GUI_windows::draw_windows(){
  //---------------------------

  win_camera->window();
  win_object->window();
  win_set->window();

  //---------------------------
}
