#ifndef VK_COMMAND_H
#define VK_COMMAND_H

#include "../VK_parameter.h"
#include "../../../common.h"

class Engine;
class Param_engine;
class VK_device;
class VK_swapchain;
class VK_renderpass;
class VK_pipeline;
class VK_framebuffer;
class VK_descriptor;
class VK_viewport;
class VK_window;
class VK_buffer;


class VK_command
{
public:
  //Constructor / Destructor
  VK_command(Engine* engineManager);
  ~VK_command();

public:
  //Main functions
  void create_command_pool();
  void create_command_buffers();
  void cleanup();

  void record_command_buffer(VkCommandBuffer command_buffer, uint32_t imageIndex);
  void command_drawing(VkCommandBuffer command_buffer);
  void command_pipeline(VkCommandBuffer command_buffer);
  void command_viewport(VkCommandBuffer command_buffer);

  //One time command
  VkCommandBuffer command_buffer_begin();
  void command_buffer_end(VkCommandBuffer command_buffer);

  inline std::vector<VkCommandBuffer> get_command_buffer_vec(){return command_buffer_vec;}
  inline VkCommandBuffer get_current_command_buffer(){return command_buffer_vec[currentFrame];}
  inline VkCommandPool get_command_pool(){return command_pool;}

private:
  Engine* engineManager;
  Param_engine* param_engine;
  VK_device* vk_device;
  VK_swapchain* vk_swapchain;
  VK_renderpass* vk_renderpass;
  VK_pipeline* vk_pipeline;
  VK_framebuffer* vk_framebuffer;
  VK_descriptor* vk_descriptor;
  VK_viewport* vk_viewport;
  VK_window* vk_window;
  VK_buffer* vk_buffer;

  VkCommandPool command_pool;
  std::vector<VkCommandBuffer> command_buffer_vec;
};

#endif
