#ifndef GUI_CONTROL_H
#define GUI_CONTROL_H

#include "../common.h"

#include "../../extern/imgui/imgui.h"
#include "../../extern/imgui/imgui_impl_glfw.h"
#include "../../extern/imgui/imgui_impl_vulkan.h"

class Node_engine;
class Dimension;
class Control;


class GUI_control
{
public:
  //Constructor / Destructor
  GUI_control(Node_engine* node_engine);
  ~GUI_control();

public:
  //Main function
  void make_control();

  //Mouse function
  void control_mouse();
  void control_mouse_wheel();

  //Keyboard function
  void control_keyboard_oneAction();
  void control_keyboard_camMove();

private:
  Node_engine* node_engine;
  Dimension* dimManager;
  Control* controlManager;
};

#endif
