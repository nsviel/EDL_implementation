#ifndef GUI_STYLE_H
#define GUI_STYLE_H

#include "../../common.h"

class Node_gui;


class GUI_style
{
public:
  //Constructor / Destructor
  GUI_style(Node_gui* node_gui);
  ~GUI_style();

public:
  //Main function
  void gui_style();

  //Subfunction
  void style_window();
  void style_widget();

private:
};


#endif
