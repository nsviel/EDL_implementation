#ifndef GUI_TEXT_EDITOR_H
#define GUI_TEXT_EDITOR_H

#include "../../common.h"
#include "../../../extern/imgui/TextEditor.h"

class Node_gui;


class GUI_editor
{
public:
  //Constructor / Destructor
  GUI_editor(Node_gui* node_gui);
  ~GUI_editor();

public:
  //Main functions
  void design_panel();

private:
  TextEditor* editor;
};

#endif
