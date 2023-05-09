#ifndef WIN_CAMERA_H
#define WIN_CAMERA_H

#include "WIN_base.h"
#include "../../common.h"

class Node_gui;
class Param_gui;
class Cam;


class WIN_camera : public WIN_base
{
public:
  //Constructor / Destructor
  WIN_camera(Node_gui* node_gui, bool* show_window, string name);
  ~WIN_camera();

  //Main function
  void design_window();

  //Sub functions
  void cam_parameter();
  void cam_info();
  void cam_definedPosition();

private:
  Param_gui* param_gui;
  Cam* camera;

  int item_width;
};

#endif