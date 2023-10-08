#ifndef WIN_SET_H
#define WIN_SET_H

#include <Panel/BASE_panel.h>
#include <Specific/common.h>

class GUI;
class GUI_param;


class GUI_set : public BASE_panel
{
public:
  //Constructor / Destructor
  GUI_set(GUI* gui, bool* show_window, string name);
  ~GUI_set();

  //Main function
  void design_window();

  //Sub functions
  void set_info(Set* set);
  void set_parameter(Set* set);

  inline void set_selected_set(Set* set){this->set_selected = set;}

private:
  GUI_param* gui_param;

  Set* set_selected;
  int item_width;
};

#endif
