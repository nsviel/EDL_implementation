#ifndef NODE_GUI_H
#define NODE_GUI_H

#include "../common.h"

class Node_engine;
class GUI_left_panel;
class GUI_control;


class Node_gui
{
public:
  //Constructor / Destructor
  Node_gui(Node_engine* node_engine);
  ~Node_gui();

public:
  void loop();

  inline Node_engine* get_node_engine(){return node_engine;}
  inline GUI_left_panel* get_gui_left_panel(){return gui_left_panel;}
  inline GUI_control* get_gui_control(){return gui_control;}

private:
  Node_engine* node_engine;
  GUI_left_panel* gui_left_panel;
  GUI_control* gui_control;
};

#endif
