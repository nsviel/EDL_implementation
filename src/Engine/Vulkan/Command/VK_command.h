#ifndef VK_COMMAND_H
#define VK_COMMAND_H

#include "../Struct/struct_frame.h"
#include "../../../common.h"

class Engine;
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
class VK_command_RP;


class VK_command
{
public:
  //Constructor / Destructor
  VK_command(Engine* engineManager);
  ~VK_command();

public:
  //Main functions
  void create_command_pool();
  void create_command_buffer(vector<Frame_inflight*> vec_frame);
  void cleanup();

  //Drawing command
  void record_command_buffer(VkCommandBuffer command_buffer);
  VkCommandBuffer command_buffer_begin();
  void command_buffer_end(VkCommandBuffer command_buffer);

  inline VkCommandPool get_command_pool(){return command_pool;}

private:
  Engine* engineManager;
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
  VK_command_RP* vk_command_RP;

  VkCommandPool command_pool;
};

#endif
