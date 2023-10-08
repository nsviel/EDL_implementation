#ifndef GUI_PANEL_H
#define GUI_PANEL_H

#include <Specific/common.h>

class GUI;
class Render_node;
class GUI_timing;
class GUI_object;
class GUI_menubar;
class GUI_shader;
class GUI_editor_text;
class GUI_engine;
class GUI;
class GUI_database;
class GUI_camera;
class WIN_object;
class WIN_set;


class GUI_panel
{
public:
  //Constructor / Destructor
  GUI_panel(GUI* gui);
  ~GUI_panel();

public:
  //Main functions
  void draw_panels();

  //Subfunction
  void docker_space_main();
  void set_initial_panel_focus();

private:
  GUI* gui;
  Render_node* render_node;

  GUI_timing* gui_timing;
  GUI_object* gui_object;
  GUI_menubar* gui_menubar;
  GUI_shader* gui_shader;
  GUI_editor_text* gui_editor_text;
  GUI_engine* gui_engine;
  GUI_database* gui_database;
  WIN_object* win_object;
  GUI_camera* win_camera;
  WIN_set* win_set;
};

#endif
