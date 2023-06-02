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


class VK_command
{
public:
  //Constructor / Destructor
  VK_command(VK_engine* vk_engine);
  ~VK_command();

public:
  //Main functions
  void create_command_pool();
  void allocate_command_buffer(vector<Frame*>& vec_frame);
  void clean_command_pool();

  //Command buffer
  void start_command_buffer(VkCommandBuffer& command_buffer);
  void stop_command_buffer(VkCommandBuffer& command_buffer);

  //Render pass
  void start_render_pass(VkCommandBuffer& command_buffer, Struct_renderpass* renderpass);
  void stop_render_pass(VkCommandBuffer& command_buffer);

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

  VkCommandPool command_pool;
};

#endif
