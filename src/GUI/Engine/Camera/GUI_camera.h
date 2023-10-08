#ifndef WIN_CAMERA_H
#define WIN_CAMERA_H

#include <Panel/BASE_panel.h>
#include <Specific/common.h>

class GUI;
class GUI_param;
class Struct_camera;


class GUI_camera : public BASE_panel
{
public:
  //Constructor / Destructor
  GUI_camera(GUI* gui, bool* show_window, string name);
  ~GUI_camera();

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
