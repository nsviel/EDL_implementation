#ifndef GUI_EDITOR_NODE_H
#define GUI_EDITOR_NODE_H

#include <Specific/common.h>
#include <imgui/node/imgui_node_editor.h>

class GUI_editor_node;


class GUI_editor_node
{
public:
  //Constructor / Destructor
  GUI_editor_node(GUI_editor_node* gui);
  ~GUI_editor_node();

public:
  //Main functions
  void design_panel();

  //Subfunction
  void node_editor();

private:
};

#endif
