#ifndef GUI_KEYBOARD_H
#define GUI_KEYBOARD_H

#include <Specific/common.h>

class GUI;
class Window;
class Camera;
class Window;
class Scene;
class Transformation;


class GUI_keyboard
{
public:
  //Constructor / Destructor
  GUI_keyboard(GUI* gui);
  ~GUI_keyboard();

public:
  //Main function
  void run_control();

  //Keyboard function
  void control_keyboard_oneAction();
  void control_keyboard_camMove();
  void control_keyboard_translation();

private:
  Window* window;
  Scene* sceneManager;
  Camera* cameraManager;
  Transformation* transformManager;
};

#endif
