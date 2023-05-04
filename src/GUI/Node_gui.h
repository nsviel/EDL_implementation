#ifndef NODE_GUI_H
#define NODE_GUI_H

#include "../common.h"

class Node_engine;
class GUI;


class Node_gui
{
public:
  //Constructor / Destructor
  Node_gui(Node_engine* node_engine);
  ~Node_gui();

public:
  void loop();

  inline Node_engine* get_node_engine(){return node_engine;}
  inline GUI* get_guiManager(){return guiManager;}

private:
  Node_engine* node_engine;
  GUI* guiManager;
};

#endif
