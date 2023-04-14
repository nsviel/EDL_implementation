#ifndef VK_COMMAND_H
#define VK_COMMAND_H

#include <vulkan/vulkan.h>

#include "../../common.h"

class Engine_vulkan;
class VK_device;


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

  inline VkCommandPool get_commandPool(){return commandPool;}
  inline std::vector<VkCommandBuffer> get_commandBuffers(){return commandBuffers;}

private:
  Engine_vulkan* engine_vulkan;
  VK_device* vk_device;

  VkCommandPool commandPool;
  std::vector<VkCommandBuffer> commandBuffers;
};

#endif
