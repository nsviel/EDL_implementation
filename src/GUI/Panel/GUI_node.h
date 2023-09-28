#ifndef GUI_NODE_H
#define GUI_NODE_H

#include "../../common.h"
#include "../../../extern/imgui/node/imgui_node_editor.h"

class Node_gui;


class GUI_node
{
public:
  //Constructor / Destructor
  GUI_node(Node_gui* node_gui);
  ~GUI_node();

public:
  //Main functions
  void design_panel();

  //Subfunction
  void node_editor();

private:
  TextEditor* editor;
};

#endif
