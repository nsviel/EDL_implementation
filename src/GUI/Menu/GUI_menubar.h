#ifndef GUI_MENUBAR_H
#define GUI_MENUBAR_H

#include "../../common.h"

class Node_gui;
class Loader;
class GUI_param;
class GUI_init;
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
  void menu_demo();

private:
  Node_gui* node_gui;
  Loader* loaderManager;
  GUI_init* gui_init;
  GUI_param* gui_param;
  GUI_option* gui_option;

  bool show_demo;

};


#endif
