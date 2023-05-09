#ifndef GUI_MENUBAR_H
#define GUI_MENUBAR_H

#include "../../common.h"

class Node_gui;
class Param_gui;
class GUI_option;


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
  void menu_icons();

private:
  Node_gui* node_gui;
  Param_gui* param_gui;
  GUI_option* gui_option;
};


#endif
