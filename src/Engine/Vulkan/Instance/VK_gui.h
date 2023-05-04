#ifndef VK_GUI_H
#define VK_GUI_H

#include "../../../common.h"

#include "../../../../extern/imgui/imgui.h"
#include "../../../../extern/imgui/imgui_impl_glfw.h"
#include "../../../../extern/imgui/imgui_impl_vulkan.h"

class Engine_vulkan;


class VK_gui
{
public:
  //Constructor / Destructor
  VK_gui(Engine_vulkan* engine_vulkan);
  ~VK_gui();

public:
  //Main functions
  void init_gui();
  void cleanup();
  void command_gui(VkCommandBuffer command_buffer);

  //Loop functions
  void loop_start();
  void loop_end();

private:
  Engine_vulkan* engine_vulkan;

  VkDescriptorPool imguiPool;
  ImDrawData* draw_data;
};

#endif
