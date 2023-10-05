#ifndef GPU_GUI_H
#define GPU_GUI_H

#include "../Render_common.h"
#include "../Vulkan/Struct/struct_renderpass.h"

class VK_engine;
class VK_param;
class VK_command_buffer;
class VK_command;
class VK_window;


class GPU_gui
{
public:
  //Constructor / Destructor
  GPU_gui(VK_engine* vk_engine);
  ~GPU_gui();

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
  VK_command* vk_command;
  VK_window* vk_window;

  VkDescriptorPool imguiPool;
  ImDrawData* draw_data;
};

#endif
