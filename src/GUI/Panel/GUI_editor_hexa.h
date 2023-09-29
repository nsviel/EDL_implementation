#ifndef GUI_EDITOR_HEXA_H
#define GUI_EDITOR_HEXA_H

#include "../../common.h"
#include "../../../extern/imgui/editor/editor_memory.h"

class Node_gui;


class GUI_editor_hexa
{
public:
  //Constructor / Destructor
  GUI_editor_hexa(Node_gui* node_gui);
  ~GUI_editor_hexa();

public:
  //Main functions
  void design_panel();

  //Subfunction
  void design_editor_memory();

private:
};

#endif
