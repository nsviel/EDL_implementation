#ifndef GUI_FILEMANAGER_H
#define GUI_FILEMANAGER_H

#include "../../common.h"

class Node_gui;
class GUI_param;
class Database;


class GUI_filemanager
{
public:
  //Constructor / Destructor
  GUI_filemanager(Node_gui* node_gui);
  ~GUI_filemanager();

public:
  //Main function
  void design_panel();

  //Subfunction
  void tree_view(float width);
  int data_node_tree(Set* set);

private:
  GUI_param* gui_param;
  Database* dataManager;
};

#endif
