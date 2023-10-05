#ifndef GUI_PANEL_H
#define GUI_PANEL_H

#include "../../common.h"

class Node_gui;
class Render_node;
class Dimension;
class GUI_profiling;
class GUI_object;
class GUI_menubar;
class GUI_shader;
class GUI_editor_text;
class GUI_engine;
class GUI_node;
class GUI_database;


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
  void set_initial_panel_focus();

private:
  Node_gui* node_gui;
  Render_node* core_node;
  Dimension* dimManager;

  GUI_profiling* gui_profiling;
  GUI_object* gui_object;
  GUI_menubar* gui_menubar;
  GUI_shader* gui_shader;
  GUI_editor_text* gui_editor_text;
  GUI_engine* gui_engine;
  GUI_node* gui_node;
  GUI_database* gui_database;
};

#endif
