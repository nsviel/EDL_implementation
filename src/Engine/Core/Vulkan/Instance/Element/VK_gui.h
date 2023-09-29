#ifndef VK_GUI_H
#define VK_GUI_H

#include "../../Struct/struct_renderpass.h"
#include "../../../../common.h"

#include "../../../../../../extern/imgui/core/imgui.h"
#include "../../../../../../extern/imgui/core/imgui_impl_glfw.h"
#include "../../../../../../extern/imgui/vulkan/imgui_impl_vulkan.h"

class VK_engine;
class VK_param;
class VK_command_buffer;
class VK_window;
class VK_instance;
class VK_device;
class VK_renderpass;
class VK_physical_device;
class VK_frame;


class VK_gui
{
public:
  //Constructor / Destructor
  VK_gui(VK_engine* vk_engine);
  ~VK_gui();

public:
  //Main functions
  void clean_gui();
  void command_gui(Struct_renderpass* renderpass);

  //Init function
  void init_gui();
  void gui_vulkan();
  void gui_select_font();
  void gui_load_font();

  //Loop functions
  void loop_start();
  void loop_end();

private:
  VK_engine* vk_engine;
  VK_param* vk_param;
  VK_command_buffer* vk_command_buffer;
  VK_window* vk_window;
  VK_instance* vk_instance;
  VK_device* vk_device;
  VK_renderpass* vk_renderpass;
  VK_physical_device* vk_physical_device;
  VK_frame* vk_frame;

  VkDescriptorPool imguiPool;
  ImDrawData* draw_data;
};

#endif
