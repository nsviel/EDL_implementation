#ifndef VK_BUFFER_H
#define VK_BUFFER_H

#include "../Struct/struct_data.h"
#include "../../../common.h"

class Engine;
class Param_vulkan;
class VK_device;
class VK_physical_device;


class VK_buffer
{
public:
  //Constructor / Destructor
  VK_buffer(Engine* engineManager);
  ~VK_buffer();

public:
  //Main functions
  void create_buffer(Struct_data* data);
  void clean_data(Struct_data* data);

  //Data buffer functions
  void create_buffer_uv(Struct_data* data);
  void create_buffer_xyz(Struct_data* data);
  void create_buffer_rgb(Struct_data* data);

  //Buffer functions
  void bind_buffer_memory(VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
  void create_gpu_buffer(VkDeviceSize size, VkBufferUsageFlags usage, VkBuffer& buffer);
  void copy_buffer_to_gpu(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

  //Specific functions
  uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
  void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);

private:
  Engine* engineManager;
  Param_vulkan* param_vulkan;
  VK_device* vk_device;
  VK_physical_device* vk_physical_device;
};

#endif
