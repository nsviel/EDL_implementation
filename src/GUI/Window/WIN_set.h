#ifndef WIN_SET_H
#define WIN_SET_H

#include "WIN_base.h"
#include "../../common.h"

class Node_gui;
class GUI_param;


class WIN_set : public WIN_base
{
public:
  //Constructor / Destructor
  WIN_set(Node_gui* node_gui, bool* show_window, string name);
  ~WIN_set();

  //Main function
  void design_window();

  //Sub functions
  void set_info(Set* set);

private:
  GUI_param* gui_param;

  int item_width;
};

#endif
