#ifndef GUI_EDITOR_HEXA_H
#define GUI_EDITOR_HEXA_H

#include "../GUI_common.h"
#include <imgui/editor/editor_memory.h>

class GUI_node;


class GUI_editor_hexa
{
public:
  //Constructor / Destructor
  GUI_editor_hexa(GUI_node* gui_node);
  ~GUI_editor_hexa();

public:
  //Main functions
  void design_panel();

  //Subfunction
  void design_editor_memory();

private:
};

#endif
