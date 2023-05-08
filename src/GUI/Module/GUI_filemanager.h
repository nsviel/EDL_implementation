#ifndef GUI_FILEMANAGER_H
#define GUI_FILEMANAGER_H

#include "../../common.h"

class Node_gui;


class GUI_filemanager
{
public:
  //Constructor / Destructor
  GUI_filemanager(Node_gui* node_gui);
  ~GUI_filemanager();

public:
  void tree_view();

private:

};

#endif
