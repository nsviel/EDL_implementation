#ifndef GUI_STYLE_H
#define GUI_STYLE_H

#include "../GUI_common.h"

class GUI_node;


class GUI_style
{
public:
  //Constructor / Destructor
  GUI_style(GUI_node* gui_node);
  ~GUI_style();

public:
  //Main function
  void gui_style();

  //Subfunction
  void style_window();
  void color_window();
  void color_widget();

private:
};


#endif
