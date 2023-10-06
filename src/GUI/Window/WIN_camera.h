#ifndef WIN_CAMERA_H
#define WIN_CAMERA_H

#include "WIN_base.h"
#include <Specific/common.h>

class GUI_node;
class GUI_param;
class Struct_camera;


class WIN_camera : public WIN_base
{
public:
  //Constructor / Destructor
  WIN_camera(GUI_node* gui_node, bool* show_window, string name);
  ~WIN_camera();

  //Main function
  void design_window();

  //Sub functions
  void cam_parameter();
  void cam_info();
  void cam_definedPosition();

private:
  GUI_param* gui_param;
  Struct_camera* camera;

  int item_width;
};

#endif
