#ifndef GUI_EDITOR_TEXT_H
#define GUI_EDITOR_TEXT_H

#include "../../common.h"
#include <imgui/editor/editor_text.h>

class Node_gui;


class GUI_editor_text
{
public:
  //Constructor / Destructor
  GUI_editor_text(Node_gui* node_gui);
  ~GUI_editor_text();

public:
  //Main functions
  void design_panel();

  //Subfunction
  void load_file(string path);

private:
  TextEditor* editor;
};

#endif
