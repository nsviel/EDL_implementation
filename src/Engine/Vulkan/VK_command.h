#ifndef VK_COMMAND_H
#define VK_COMMAND_H

#include <vulkan/vulkan.h>

#include "../../common.h"

class Engine_vulkan;
class VK_device;
class VK_swapchain;
class VK_renderpass;
class VK_pipeline;
class VK_framebuffer;
class VK_buffer;


class VK_command
{
public:
  //Constructor / Destructor
  VK_command(Engine_vulkan* engine_vulkan);
  ~VK_command();

public:
  //Main functions
  void create_command_pool();
  void create_command_buffers();
  void cleanup();

  void record_command_buffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);

  inline VkCommandPool get_command_pool(){return command_pool;}
  inline std::vector<VkCommandBuffer> get_command_buffer_vec(){return command_buffer_vec;}

private:
  Engine_vulkan* engine_vulkan;
  VK_device* vk_device;
  VK_swapchain* vk_swapchain;
  VK_renderpass* vk_renderpass;
  VK_pipeline* vk_pipeline;
  VK_buffer* vk_buffer;
  VK_framebuffer* vk_framebuffer;

  VkCommandPool command_pool;
  std::vector<VkCommandBuffer> command_buffer_vec;
};

#endif
