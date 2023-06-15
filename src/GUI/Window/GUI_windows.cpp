#include "GUI_windows.h"

#include "WIN_camera.h"
#include "WIN_data.h"

#include "../Node_gui.h"
#include "../GUI_param.h"


//Constructor / Destructor
GUI_windows::GUI_windows(Node_gui* node_gui){
  //---------------------------

  this->gui_param = node_gui->get_param_gui();
  this->win_camera = new WIN_camera(node_gui, &gui_param->show_camera, "Camera");
  this->win_data = new WIN_data(node_gui, &gui_param->show_data, "Data");

  //---------------------------
}
GUI_windows::~GUI_windows(){}

//Main function
void GUI_windows::draw_windows(){
  //---------------------------

  win_camera->window();
  win_data->window();

  //---------------------------
}
