#ifndef VK_UNIFORM_H
#define VK_UNIFORM_H

#include <vulkan/vulkan.h>

#include "../../../common.h"

class Engine_vulkan;
class VK_device;
class VK_buffer;
class VK_swapchain;
class Camera;


class VK_uniform
{
public:
  //Constructor / Destructor
  VK_uniform(Engine_vulkan* engine_vulkan);
  ~VK_uniform();

public:
  //Main functions
  void create_uniform_buffers();
  void update_uniform_buffer(uint32_t currentImage);
  void cleanup();

  inline std::vector<VkBuffer> get_uniformBuffers(){return uniformBuffers;};

private:
  VK_device* vk_device;
  VK_buffer* vk_buffer;
  VK_swapchain* vk_swapchain;
  Camera* vk_camera;

  std::vector<VkBuffer> uniformBuffers;
  std::vector<VkDeviceMemory> uniformBuffersMemory;
  std::vector<void*> uniformBuffersMapped;
};

#endif
