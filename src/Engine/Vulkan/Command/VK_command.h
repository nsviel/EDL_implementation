#ifndef VK_COMMAND_H
#define VK_COMMAND_H

#include "../Struct/struct_frame.h"
#include "../../../common.h"

class VK_engine;
class Param_vulkan;
class Param_engine;

class VK_device;
class VK_renderpass;
class VK_pipeline;
class VK_viewport;
class VK_window;
class VK_buffer;
class VK_camera;
class VK_physical_device;
class VK_frame;
class VK_canvas;
class VK_uniform;
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
  void create_command_buffer(vector<Frame_inflight*> vec_frame_inflight);
  void cleanup();

  //Drawing command
  void record_command_buffer(VkCommandBuffer& command_buffer);
  VkCommandBuffer singletime_command_buffer_begin();
  void singletime_command_buffer_end(VkCommandBuffer command_buffer);

  inline VkCommandPool get_command_pool(){return command_pool;}

private:
  VK_engine* vk_engine;
  Param_vulkan* param_vulkan;
  Param_engine* param_engine;
  VK_device* vk_device;
  VK_renderpass* vk_renderpass;
  VK_pipeline* vk_pipeline;
  VK_viewport* vk_viewport;
  VK_window* vk_window;
  VK_buffer* vk_buffer;
  VK_camera* vk_camera;
  VK_frame* vk_frame;
  VK_physical_device* vk_physical_device;
  VK_canvas* vk_canvas;
  VK_uniform* vk_uniform;
  VK_cmd* vk_cmd;

  VkCommandPool command_pool;
};

#endif
