#ifndef VK_UNIFORM_H
#define VK_UNIFORM_H

#include "../Struct/struct_mvp.h"
#include "../../../common.h"

class Engine;
class VK_device;
class VK_buffer;
class VK_swapchain;
class VK_camera;


class VK_uniform
{
public:
  //Constructor / Destructor
  VK_uniform(Engine* engineManager);
  ~VK_uniform();

public:
  //Main functions
  void create_uniform_buffers();
  void update_uniform_buffer(uint32_t currentImage, MVP& mvp);
  void cleanup();

  inline std::vector<VkBuffer> get_uniformBuffers(){return uniform_buffer;};

private:
  VK_device* vk_device;
  VK_buffer* vk_buffer;
  VK_swapchain* vk_swapchain;
  VK_camera* vk_camera;

  std::vector<VkBuffer> uniform_buffer;
  std::vector<VkDeviceMemory> uniform_buffer_memory;
  std::vector<void*> uniform_buffer_mapped;
};

#endif
