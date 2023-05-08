#ifndef GUI_CONTROL_H
#define GUI_CONTROL_H

#include "../../common.h"

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
  void make_control();

  //Mouse function
  void control_mouse();
  void control_mouse_wheel();

  //Keyboard function
  void control_keyboard_oneAction();
  void control_keyboard_camMove();

private:
  Dimension* dimManager;
  Control* controlManager;
  Camera* cameraManager;
};

#endif
