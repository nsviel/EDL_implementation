#ifndef GUI_OBJECT_H
#define GUI_OBJECT_H

#include "../../common.h"

class Node_gui;
class GUI_param;
class Database;


class GUI_object
{
public:
  //Constructor / Destructor
  GUI_object(Node_gui* node_gui);
  ~GUI_object();

public:
  //Main function
  void design_panel();

  //Subfunction
  void draw_window_background();
  void tree_view();
  int data_node_tree(Set* set);

private:
  GUI_param* gui_param;
  Database* dataManager;
};

#endif
