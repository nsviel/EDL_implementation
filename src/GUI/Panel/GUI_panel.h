#ifndef GUI_PANEL_H
#define GUI_PANEL_H

#include "../../common.h"

class Node_gui;
class Node_engine;
class Dimension;
class GUI_profiling;
class GUI_filemanager;
class GUI_menubar;
class GUI_shader;
class GUI_editor;
class GUI_engine;
class GUI_node;


class GUI_panel
{
public:
  //Constructor / Destructor
  GUI_panel(Node_gui* node_gui);
  ~GUI_panel();

public:
  //Main functions
  void draw_panels();

  //Subfunction
  void docker_space_main();

private:
  Node_gui* node_gui;
  Node_engine* node_engine;
  Dimension* dimManager;

  GUI_profiling* gui_profiling;
  GUI_filemanager* gui_filemanager;
  GUI_menubar* gui_menubar;
  GUI_shader* gui_shader;
  GUI_editor* gui_editor;
  GUI_engine* gui_engine;
  GUI_node* gui_node;
};

#endif
