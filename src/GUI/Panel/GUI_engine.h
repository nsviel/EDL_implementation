#ifndef GUI_ENGINE_H
#define GUI_ENGINE_H

#include "../../common.h"

class Node_gui;
class VK_param;
class GUI_control;


class GUI_engine
{
public:
  //Constructor / Destructor
  GUI_engine(Node_gui* node_gui);
  ~GUI_engine();

public:
  //Main functions
  void design_panel();

  //Subfunction
  void engine_window();

private:
  VK_param* vk_param;
  GUI_control* gui_control;

  VkDescriptorSet descriptor;
  bool has_been_initialized;
};

#endif
