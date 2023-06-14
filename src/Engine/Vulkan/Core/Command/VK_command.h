#ifndef VK_COMMAND_H
#define VK_COMMAND_H

#include "../../Struct/struct_frame.h"
#include "../../Struct/struct_data.h"
#include "../../Struct/struct_renderpass.h"
#include "../../../../common.h"

class Param_engine;
class VK_engine;
class VK_param;
class VK_renderpass;
class VK_physical_device;
class VK_cmd;
class VK_pipeline;
class VK_command_buffer;
class VK_descriptor;


class VK_command
{
public:
  //Constructor / Destructor
  VK_command(VK_engine* vk_engine);
  ~VK_command();

public:
  //Command buffer
  void start_command_buffer(Struct_renderpass* renderpass);
  void stop_command_buffer(Struct_renderpass* renderpass);

  //Render pass
  void start_render_pass(Struct_renderpass* renderpass, Frame* frame);
  void stop_render_pass(Struct_renderpass* renderpass);

  //Image layout transition
  void image_layout_transition(VkCommandBuffer command_buffer, Struct_image* image, VkImageLayout oldLayout, VkImageLayout newLayout);
  void image_layout_transition_single(Struct_image* image, VkImageLayout old_layout, VkImageLayout new_layout);

  //Single time command
  VkCommandBuffer singletime_command_begin();
  void singletime_command_end(VkCommandBuffer command_buffer);

private:
  Param_engine* param_engine;
  VK_engine* vk_engine;
  VK_param* vk_param;
  VK_renderpass* vk_renderpass;
  VK_physical_device* vk_physical_device;
  VK_command_buffer* vk_command_buffer;
  VK_cmd* vk_cmd;
  VK_pipeline* vk_pipeline;
  VK_descriptor* vk_descriptor;
};

#endif
