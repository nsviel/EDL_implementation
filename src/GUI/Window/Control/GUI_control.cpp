#include "GUI_control.h"
#include "GUI_keyboard.h"
#include "GUI_mouse.h"

#include <GUI.h>


//Constructor / Destructor
GUI_control::GUI_control(GUI* gui){
  //---------------------------

  this->gui_mouse = new GUI_mouse(gui);
  this->gui_keyboard = new GUI_keyboard(gui);

  //---------------------------
}
GUI_control::~GUI_control(){}

//Main function
void GUI_control::run_control(ImVec2 center){
  //---------------------------

  gui_keyboard->run_control();
  gui_mouse->run_control(center);

  //---------------------------
}
