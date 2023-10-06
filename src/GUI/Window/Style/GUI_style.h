#ifndef GUI_STYLE_H
#define GUI_STYLE_H

#include <Specific/common.h>

class GUI;


class GUI_style
{
public:
  //Constructor / Destructor
  GUI_style(GUI* gui);
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
