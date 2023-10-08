#ifndef GUI_CONTROL_H
#define GUI_CONTROL_H

#include <Specific/common.h>

class GUI;
class GUI_mouse;
class GUI_keyboard;


class GUI_control
{
public:
  //Constructor / Destructor
  GUI_control(GUI* gui);
  ~GUI_control();

public:
  //Main function
  void run_control(ImVec2 center);

private:
  GUI_mouse* gui_mouse;
  GUI_keyboard* gui_keyboard;
};

#endif
