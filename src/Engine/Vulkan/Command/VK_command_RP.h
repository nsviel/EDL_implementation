#ifndef VK_COMMAND_RP_H
#define VK_COMMAND_RP_H

#include "../../../common.h"

class Engine;
class Param_vulkan;
class VK_viewport;
class VK_pipeline;
class VK_camera;
class VK_frame;
class VK_canvas;
class VK_uniform;
class VK_data;


class VK_command_RP
{
public:
  //Constructor / Destructor
  VK_command_RP(Engine* engineManager);
  ~VK_command_RP();

public:
  //Renderpass command
  void command_viewport(VkCommandBuffer command_buffer);
  void command_drawing_scene(VkCommandBuffer command_buffer);
  void command_drawing_glyph(VkCommandBuffer command_buffer);
  void command_drawing_canvas(VkCommandBuffer command_buffer);

private:
  Engine* engineManager;
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
