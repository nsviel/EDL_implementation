#ifndef WIN_DATA_H
#define WIN_DATA_H

#include "WIN_base.h"
#include "../../common.h"

class Node_gui;
class GUI_param;
class Struct_camera;


class WIN_data : public WIN_base
{
public:
  //Constructor / Destructor
  WIN_data(Node_gui* node_gui, bool* show_window, string name);
  ~WIN_data();

  //Main function
  void design_window();

  //Sub functions
  void object_parameter();
  void option_line_width();

private:
  GUI_param* gui_param;
  Struct_camera* camera;

  int item_width;
};

#endif
