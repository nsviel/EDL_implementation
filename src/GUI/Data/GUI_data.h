#ifndef GUI_DATA_H
#define GUI_DATA_H

#include "../../common.h"

class Node_gui;
class Node_engine;
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
  void option_line_width();

private:
  Node_gui* node_gui;
  Node_engine* node_engine;
  VK_engine* vk_engine;
  VK_param* vk_param;

  int width;
};

#endif
