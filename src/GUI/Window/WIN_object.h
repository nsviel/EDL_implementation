#ifndef WIN_DATA_H
#define WIN_DATA_H

#include "WIN_base.h"
#include <Specific/common.h>

class GUI_node;
class GUI_param;
class Control;

class WIN_object : public WIN_base
{
public:
  //Constructor / Destructor
  WIN_object(GUI_node* gui_node, bool* show_window, string name);
  ~WIN_object();

  //Main function
  void design_window();

  //Sub functions
  void object_info(Object* object);
  void object_parameter(Object* object);

  //Primitive size
  void width_line(Object* object);
  void size_point(Object* object);

private:
  GUI_param* gui_param;
  Control* controlManager;

  int item_width;
};

#endif
