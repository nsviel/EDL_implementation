#ifndef GUI_LEFT_PAN_H
#define GUI_LEFT_PAN_H

#include "../../common.h"

class Node_gui;
class Dimension;
class GUI_option;
class GUI_filemanager;


class GUI_left_panel
{
public:
  //Constructor / Destructor
  GUI_left_panel(Node_gui* node_gui);
  ~GUI_left_panel();

public:
  //Main functions
  void draw_left_panel();
  void left_panel_dim();
  void left_panel_menu();
  void left_panel_content();

private:
  Node_gui* node_gui;
  Dimension* dimManager;
  GUI_option* gui_option;
  GUI_filemanager* gui_filemanager;
};

#endif
