#ifndef WIN_BASE_H
#define WIN_BASE_H

#include "../../common.h"


class WIN_base
{
public:
  //Constructor / Destructor
  WIN_base(bool* show_window, string name);
  ~WIN_base();

public:
  //Main function
  void window();

  //Subfunction
  virtual void design_window();

private:
  string name;
  int item_width;
  bool* show_window;
};

#endif
