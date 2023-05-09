#ifndef VK_GUI_H
#define VK_GUI_H

#include "../../../common.h"

#include "../../../../extern/imgui/imgui.h"
#include "../../../../extern/imgui/imgui_impl_glfw.h"
#include "../../../../extern/imgui/imgui_impl_vulkan.h"

class Engine;
class VK_command;
class VK_window;
class VK_instance;
class VK_device;
class VK_renderpass;


class VK_gui
{
public:
  //Constructor / Destructor
  VK_gui(Engine* engineManager);
  ~VK_gui();

public:
  //Main functions
  void cleanup();
  void command_gui(VkCommandBuffer command_buffer);

  //Init function
  void init_gui();
  void gui_vulkan();
  void gui_style();
  void gui_font();
  void gui_font_load();

  //Loop functions
  void loop_start();
  void loop_end();

private:
  Engine* engineManager;
  VK_command* vk_command;
  VK_window* vk_window;
  VK_instance* vk_instance;
  VK_device* vk_device;
  VK_renderpass* vk_renderpass;

  VkDescriptorPool imguiPool;
  ImDrawData* draw_data;
};

#endif
