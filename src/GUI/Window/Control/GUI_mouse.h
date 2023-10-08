#ifndef GUI_MOUSE_H
#define GUI_MOUSE_H

#include <Specific/common.h>

class Render_param;
class GUI;
class Window;
class Camera;
class Window;
class Transformation;
class Scene;


class GUI_mouse
{
public:
  //Constructor / Destructor
  GUI_mouse(GUI* gui);
  ~GUI_mouse();

public:
  //Main function
  void run_control(ImVec2 center);

  //Mouse function
  void control_mouse(ImVec2 center);
  void control_mouse_wheel();

private:
  Render_param* core_param;
  Window* window;
  Camera* cameraManager;
  Transformation* transformManager;
  Scene* sceneManager;
};

#endif
