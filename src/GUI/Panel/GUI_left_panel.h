#ifndef GUI_LEFT_PAN_H
#define GUI_LEFT_PAN_H

#include "../../common.h"

class Node_gui;
class Node_engine;
class Dimension;
class GUI_profiling;
class GUI_filemanager;
class GUI_menubar;
class GUI_shader;
class GUI_editor;


class GUI_left_panel
{
public:
  //Constructor / Destructor
  GUI_left_panel(Node_gui* node_gui);
  ~GUI_left_panel();

public:
  //Main functions
  void draw_left_panel();
  void design_top();
  void design_bot();

  //Subfunction
  void update_dim();

private:
  Node_gui* node_gui;
  Node_engine* node_engine;
  Dimension* dimManager;

  GUI_profiling* gui_profiling;
  GUI_filemanager* gui_filemanager;
  GUI_menubar* gui_menubar;
  GUI_shader* gui_shader;
  GUI_editor* gui_editor;
};

#endif
