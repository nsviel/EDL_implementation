#ifndef WIN_SET_H
#define WIN_SET_H

#include "WIN_base.h"
#include "../GUI_common.h"

class GUI_node;
class GUI_param;


class WIN_set : public WIN_base
{
public:
  //Constructor / Destructor
  WIN_set(GUI_node* gui_node, bool* show_window, string name);
  ~WIN_set();

  //Main function
  void design_window();

  //Sub functions
  void set_info(Set* set);
  void set_parameter(Set* set);

private:
  GUI_param* gui_param;

  int item_width;
};

#endif
