#ifndef WIN_DATA_H
#define WIN_DATA_H

#include "WIN_base.h"
#include "../../common.h"

class Node_gui;
class GUI_param;


class WIN_data : public WIN_base
{
public:
  //Constructor / Destructor
  WIN_data(Node_gui* node_gui, bool* show_window, string name);
  ~WIN_data();

  //Main function
  void design_window();

  //Sub functions
  void object_info(Object* object);
  void object_parameter(Object* object);

  //Primitive size
  void width_line(Object* object);
  void size_point(Object* object);

  inline void set_object(Object* object){this->object = object;}

private:
  GUI_param* gui_param;

  Object* object;
  int item_width;
};

#endif
