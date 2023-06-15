#ifndef GUI_WINDOWS_H
#define GUI_WINDOWS_H

#include "WIN_base.h"
#include "../../common.h"

class Node_gui;
class Param_gui;
class WIN_camera;


class GUI_windows
{
public:
  //Constructor / Destructor
  GUI_windows(Node_gui* node_gui);
  ~GUI_windows();

  //Main function
  void draw_windows();

public:
  Param_gui* param_gui;
  WIN_camera* win_camera;
};

#endif
