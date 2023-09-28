#ifndef GUI_TEXT_EDITOR_H
#define GUI_TEXT_EDITOR_H

#include "../../common.h"
#include "../../../extern/imgui/editor/editor_text.h"

class Node_gui;


class GUI_editor
{
public:
  //Constructor / Destructor
  GUI_editor(Node_gui* node_gui);
  ~GUI_editor();

public:
  //Main functions
  void design_editor_text();
  void design_editor_memory();

private:
  TextEditor* editor;
};

#endif
