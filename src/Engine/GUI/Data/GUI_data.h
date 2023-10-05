#ifndef GUI_DATA_H
#define GUI_DATA_H

#include "../../common.h"

class Node_gui;
class Render_node;
class VK_engine;
class VK_param;


class GUI_data
{
public:
  //Constructor / Destructor
  GUI_data(Node_gui* node_gui);
  ~GUI_data();

public:
  //Main function
  void design_data();

  //Subfunction


private:
  Node_gui* node_gui;
  Render_node* core_node;
  VK_engine* vk_engine;
  VK_param* vk_param;

  int width;
};

#endif
