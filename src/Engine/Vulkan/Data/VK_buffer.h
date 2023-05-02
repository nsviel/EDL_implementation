#ifndef VK_BUFFER_H
#define VK_BUFFER_H

#include "../VK_struct.h"
#include "../../../common.h"

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
  void load_model();
  void create_vertex_buffer(std::vector<Vertex> vertices);
  void cleanup();

  //Buffer functions
  void create_buffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
  void copy_buffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

  //Specific functions
  uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
  VkCommandBuffer beginSingleTimeCommands();
  void endSingleTimeCommands(VkCommandBuffer commandBuffer);
  void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);

  inline VkBuffer get_buffer_vertex(){return buffer_vertex;}
  inline VkBuffer get_buffer_color(){return rgb_buffer;}

private:
  Engine_vulkan* engine_vulkan;
  VK_device* vk_device;

  VkBuffer buffer_vertex;
  VkDeviceMemory buffer_vertex_memory;
  VkBuffer rgb_buffer;
  VkDeviceMemory rgb_bufferMemory;
};

#endif
