#ifndef GUI_EDITOR_HEXA_H
#define GUI_EDITOR_HEXA_H

#include <Specific/common.h>
#include <imgui/editor/editor_memory.h>

class GUI;


class GUI_editor_hexa
{
public:
  //Constructor / Destructor
  GUI_editor_hexa(GUI* gui);
  ~GUI_editor_hexa();

public:
  //Main functions
  void design_panel();

  //Subfunction
  void design_editor_memory();

private:
};

#endif
