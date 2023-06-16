#ifndef GUI_WINDOWS_H
#define GUI_WINDOWS_H

#include "WIN_base.h"
#include "../../common.h"

class Node_gui;
class GUI_param;

class WIN_camera;
class WIN_object;


class GUI_windows
{
public:
  //Constructor / Destructor
  GUI_windows(Node_gui* node_gui);
  ~GUI_windows();

  //Main function
  void draw_windows();

public:
  GUI_param* gui_param;

  WIN_object* win_object;
  WIN_camera* win_camera;
};

#endif
