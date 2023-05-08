#ifndef NODE_GUI_H
#define NODE_GUI_H

#include "../common.h"

class Node;
class Node_engine;
class Node_data;

class GUI_left_panel;
class GUI_control;
class GUI_option;
class GUI_filemanager;


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
  inline GUI_filemanager* get_gui_filemanager(){return gui_filemanager;}

  inline Node_engine* get_node_engine(){return node_engine;}
  inline Node_data* get_node_data(){return node_data;}

private:
  Node_engine* node_engine;
  Node_data* node_data;

  GUI_left_panel* gui_left_panel;
  GUI_control* gui_control;
  GUI_option* gui_option;
  GUI_filemanager* gui_filemanager;
};

#endif
