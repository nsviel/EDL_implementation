#ifndef GUI_OBJECT_H
#define GUI_OBJECT_H

#include <Specific/common.h>

class GUI;
class GUI_param;
class GUI_object;
class GUI_set;
class Database;


class GUI_scene
{
public:
  //Constructor / Destructor
  GUI_scene(GUI* gui);
  ~GUI_scene();

public:
  //Main function
  void design_panel();

  //Subfunction
  void draw_window_background();
  void tree_view();
  int data_node_tree(Set* set);

private:
  GUI_param* gui_param;
  GUI_object* gui_object;
  GUI_set* gui_set;
  Database* dataManager;
};

#endif
