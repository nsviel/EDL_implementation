#ifndef GUI_CONTROL_H
#define GUI_CONTROL_H

#include "../../common.h"

class Param_engine;
class Node_gui;
class Dimension;
class Camera;
class Control;


class GUI_control
{
public:
  //Constructor / Destructor
  GUI_control(Node_gui* node_gui);
  ~GUI_control();

public:
  //Main function
  void make_control(ImVec2 center);

  //Mouse function
  void control_mouse(ImVec2 center);
  void control_mouse_wheel();

  //Keyboard function
  void control_keyboard_oneAction();
  void control_keyboard_camMove();
  void control_keyboard_translation();

private:
  Param_engine* param_engine;
  Dimension* dimManager;
  Control* controlManager;
  Camera* cameraManager;
};

#endif
