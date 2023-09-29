#ifndef GUI_SHADER_H
#define GUI_SHADER_H

#include "../../common.h"

class Node_gui;
class Dimension;
class Shader_edl;


class GUI_shader
{
public:
  //Constructor / Destructor
  GUI_shader(Node_gui* node_gui);
  ~GUI_shader();

public:
  //Main function
  void design_panel();
  void design_shader();

private:
  Dimension* dimManager;
  Shader_edl* shader_edl;

  int item_width;
};

#endif
