#ifndef WIN_BASE_H
#define WIN_BASE_H

#include <Specific/common.h>


class BASE_panel
{
public:
  //Constructor / Destructor
  BASE_panel(bool* show_window, string name);
  ~BASE_panel();

public:
  //Main function
  void window();

  //Subfunction
  virtual void design_window();

  string name;

private:
  int item_width;
  bool* show_window;
};

#endif
