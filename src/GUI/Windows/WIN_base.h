#ifndef WIN_BASE_H
#define WIN_BASE_H

#include "../../common.h"

class Node_gui;


class WIN_base
{
public:
  //Constructor / Destructor
  WIN_base(Node_gui* node_gui, bool* show_window, const char* icon);
  ~WIN_base();

public:
  //Main function
  void window();

  //Subfunction
  void design_window();

private:
  Node_gui* node_gui;
  
  bool* show_window;
  const char* icon;
  int item_width;
};

#endif
