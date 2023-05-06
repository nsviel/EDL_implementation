#ifndef GUI_LEFT_PAN_H
#define GUI_LEFT_PAN_H

#include "../../common.h"

class Node;
class Dimension;
class GUI_option;


class GUI_left_panel
{
public:
  //Constructor / Destructor
  GUI_left_panel(Node* node);
  ~GUI_left_panel();

public:
  //Main functions
  void draw_left_panel();
  void left_panel_dim();
  void left_panel_menu();
  void left_panel_content();

private:
  Node* node;
  Dimension* dimManager;
  GUI_option* gui_option;
};

#endif
