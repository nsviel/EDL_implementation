#ifndef GUI_H
#define GUI_H

#include "../common.h"

#include "../../extern/imgui/imgui.h"
#include "../../extern/imgui/imgui_impl_glfw.h"
#include "../../extern/imgui/imgui_impl_vulkan.h"

class Node_engine;


class GUI
{
public:
  //Constructor / Destructor
  GUI(Node_engine* node_engine);
  ~GUI();

public:
  //Main functions
  void init();
  void cleanup();
  void command_gui(VkCommandBuffer command_buffer);

  //Loop functions
  void loop();
  void loop_start();
  void loop_run();
  void loop_end();

private:
  Node_engine* node_engine;

  VkDescriptorPool imguiPool;
  ImDrawData* draw_data;
};

#endif
