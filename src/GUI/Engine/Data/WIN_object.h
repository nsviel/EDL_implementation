#ifndef WIN_DATA_H
#define WIN_DATA_H

#include <Panel/BASE_panel.h>
#include <Specific/common.h>

class GUI;
class GUI_param;
class Control;

class WIN_object : public BASE_panel
{
public:
  //Constructor / Destructor
  WIN_object(GUI* gui, bool* show_window, string name);
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
