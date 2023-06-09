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
class VK_descriptor;


class VK_command
{
public:
  //Constructor / Destructor
  VK_command(VK_engine* vk_engine);
  ~VK_command();

public:
  //Main functions
  void create_command_pool();
  void allocate_command_buffer(Struct_renderpass* renderpass);
  void clean_command_pool();

  //Descriptor
  void update_uniform(Struct_renderpass* renderpass, string pipeline_name);
  void update_sampler(Struct_renderpass* renderpass, string pipeline_name, Struct_image* image);

  //Command buffer
  void start_command_buffer(Struct_renderpass* renderpass);
  void stop_command_buffer(Struct_renderpass* renderpass);

  //Render pass
  void start_render_pass(Struct_renderpass* renderpass);
  void start_render_pass_low(Struct_renderpass* renderpass);
  void stop_render_pass(Struct_renderpass* renderpass);

  //Image layout transition
  void image_layout_transition(VkCommandBuffer command_buffer, Struct_image* image, VkImageLayout oldLayout, VkImageLayout newLayout);
  void image_layout_transition_single(Struct_image* image, VkImageLayout old_layout, VkImageLayout new_layout);

  //Single time command
  VkCommandBuffer singletime_command_buffer_begin();
  void singletime_command_buffer_end(VkCommandBuffer command_buffer);

  inline VkCommandPool get_command_pool(){return command_pool;}

private:
  Param_engine* param_engine;
  VK_engine* vk_engine;
  VK_param* vk_param;
  VK_renderpass* vk_renderpass;
  VK_physical_device* vk_physical_device;
  VK_cmd* vk_cmd;
  VK_pipeline* vk_pipeline;
  VK_descriptor* vk_descriptor;

  VkCommandPool command_pool;
};

#endif
