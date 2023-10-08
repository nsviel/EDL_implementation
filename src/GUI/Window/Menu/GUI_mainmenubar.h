#ifndef GUI_MENUBAR_H
#define GUI_MENUBAR_H

#include <Specific/common.h>

class GUI;
class Loader;
class Panel;
class GUI_init;
class GUI_option;


class GUI_mainmenubar
{
public:
  //Constructor / Destructor
  GUI_mainmenubar(GUI* gui);
  ~GUI_mainmenubar();

public:
  //Main function
  void design_menubar();

  //Subfunctions
  void menu();
  void menu_demo();

private:
  GUI* gui;
  Loader* loaderManager;
  GUI_init* gui_init;
  Panel* panel;
  GUI_option* gui_option;

  bool show_demo;

};


#endif
