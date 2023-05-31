#ifndef VK_CMD_H
#define VK_CMD_H

#include "../../../common.h"

class VK_engine;
class Param_vulkan;
class VK_viewport;
class VK_pipeline;
class VK_camera;
class VK_frame;
class VK_canvas;
class VK_uniform;
class VK_data;


class VK_cmd
{
public:
  //Constructor / Destructor
  VK_cmd(VK_engine* vk_engine);
  ~VK_cmd();

public:
  //Renderpass command
  void cmd_viewport(VkCommandBuffer command_buffer);
  void cmd_drawing_scene(VkCommandBuffer command_buffer);
  void cmd_drawing_glyph(VkCommandBuffer command_buffer);
  void cmd_drawing_canvas(VkCommandBuffer command_buffer);

private:
  VK_engine* vk_engine;
  Param_vulkan* param_vulkan;
  VK_pipeline* vk_pipeline;
  VK_camera* vk_camera;
  VK_frame* vk_frame;
  VK_canvas* vk_canvas;
  VK_uniform* vk_uniform;
  VK_data* vk_data;
  VK_viewport* vk_viewport;
};

#endif
