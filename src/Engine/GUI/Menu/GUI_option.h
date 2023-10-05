#ifndef GUI_OPION_H
#define GUI_OPION_H

#include "../../common.h"

class Node_gui;
class Render_node;
class VK_engine;
class VK_param;


class GUI_option
{
public:
  //Constructor / Destructor
  GUI_option(Node_gui* node_gui);
  ~GUI_option();

public:
  //Main function
  void design_option();

  //Subfunctions
  void option_color();
  void option_font();
  void option_fps();

private:
  Node_gui* node_gui;
  Render_node* core_node;
  VK_engine* vk_engine;
  VK_param* vk_param;

  int width;
};

#endif
