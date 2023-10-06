#ifndef GUI_EDITOR_TEXT_H
#define GUI_EDITOR_TEXT_H

#include <Specific/common.h>
#include <imgui/editor/editor_text.h>

class GUI_node;


class GUI_editor_text
{
public:
  //Constructor / Destructor
  GUI_editor_text(GUI_node* gui_node);
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
