#ifndef GUI_SHADER_H
#define GUI_SHADER_H

#include <Specific/common.h>

class GUI_node;
class Shader_edl;


class GUI_shader
{
public:
  //Constructor / Destructor
  GUI_shader(GUI_node* gui_node);
  ~GUI_shader();

public:
  //Main function
  void design_panel();
  void design_shader();

private:
  Shader_edl* shader_edl;

  int item_width;
};

#endif
