#ifndef NODE_GUI_H
#define NODE_GUI_H

#include "../common.h"

class Node;
class GUI_left_panel;
class GUI_control;
class GUI_option;


class Node_gui
{
public:
  //Constructor / Destructor
  Node_gui(Node* node);
  ~Node_gui();

public:
  void loop();

  inline GUI_left_panel* get_gui_left_panel(){return gui_left_panel;}
  inline GUI_control* get_gui_control(){return gui_control;}
  inline GUI_option* get_gui_option(){return gui_option;}

private:
  GUI_left_panel* gui_left_panel;
  GUI_control* gui_control;
  GUI_option* gui_option;
};

#endif
