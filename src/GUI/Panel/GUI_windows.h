#ifndef GUI_WINDOWS_H
#define GUI_WINDOWS_H

#include <Specific/Base/WIN_base.h>
#include <Specific/common.h>

class GUI;
class GUI_param;

class WIN_camera;
class WIN_object;
class WIN_set;


class GUI_windows
{
public:
  //Constructor / Destructor
  GUI_windows(GUI* gui);
  ~GUI_windows();

  //Main function
  void draw_windows();

public:
  GUI_param* gui_param;

  WIN_object* win_object;
  WIN_camera* win_camera;
  WIN_set* win_set;
};

#endif
