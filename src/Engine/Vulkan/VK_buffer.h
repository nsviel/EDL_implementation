#ifndef VK_BUFFER_H
#define VK_BUFFER_H

#include <vulkan/vulkan.h>

#include "../../common.h"

class Engine_vulkan;
class VK_device;


class VK_buffer
{
public:
  //Constructor / Destructor
  VK_buffer(Engine_vulkan* engine_vulkan);
  ~VK_buffer();

public:
  //Main functions
  void create_vertex_buffer();
  void cleanup();

  //Subfunctions
  uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

  inline VkBuffer get_buffer(){return vertexBuffer;};

private:
  Engine_vulkan* engine_vulkan;
  VK_device* vk_device;

  VkBuffer vertexBuffer;
  VkDeviceMemory vertexBufferMemory;
};

#endif
