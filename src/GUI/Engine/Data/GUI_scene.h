#ifndef GUI_OBJECT_H
#define GUI_OBJECT_H

#include <Specific/common.h>

class GUI;
class Panel;
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
  Panel* panel;
  GUI_object* gui_object;
  GUI_set* gui_set;
  Database* dataManager;
};

#endif
