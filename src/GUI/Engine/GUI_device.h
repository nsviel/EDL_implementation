#ifndef GUI_DEVICE_H
#define GUI_DEVICE_H

#include "../../common.h"

class Node_gui;
class Node_engine;
class VK_engine;
class VK_param;


class GUI_device
{
public:
  //Constructor / Destructor
  GUI_device(Node_gui* node_gui);
  ~GUI_device();

public:
  //Main function
  void design_device();

private:
  Node_gui* node_gui;
  Node_engine* node_engine;
  VK_engine* vk_engine;
  VK_param* vk_param;

  int width;
};

#endif
