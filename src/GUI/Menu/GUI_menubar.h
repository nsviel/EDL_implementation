#ifndef GUI_MENUBAR_H
#define GUI_MENUBAR_H

#include "../../common.h"

class Node_gui;
class GUI_param;
class GUI_option;
class Loader;


class GUI_menubar
{
public:
  //Constructor / Destructor
  GUI_menubar(Node_gui* node_gui);
  ~GUI_menubar();

public:
  //Main function
  void design_menubar();

  //Subfunctions
  void menu();

private:
  Node_gui* node_gui;
  GUI_param* gui_param;
  GUI_option* gui_option;
  Loader* loaderManager;
};


#endif
