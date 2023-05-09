#include "GUI_windows.h"

#include "../Node_gui.h"
#include "../Param_gui.h"

#include "../Windows/WIN_camera.h"


//Constructor / Destructor
GUI_windows::GUI_windows(Node_gui* node_gui){
  //---------------------------

  this->param_gui = node_gui->get_param_gui();
  this->win_camera = new WIN_camera(node_gui, &param_gui->show_camera, "Camera");

  //---------------------------
}
GUI_windows::~GUI_windows(){}

//Main function
void GUI_windows::draw_windows(){
  //---------------------------

  win_camera->window();

  //---------------------------
}
