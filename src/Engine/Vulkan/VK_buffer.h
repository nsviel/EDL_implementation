#ifndef VK_BUFFER_H
#define VK_BUFFER_H

#include "VK_struct.h"
#include "../../common.h"

#include <vulkan/vulkan.h>

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
  void create_vertex_buffer(std::vector<Vertex> vertices);
  void create_buffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
  void create_index_buffer();
  void cleanup();

  void load_model();

  //Subfunctions
  uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
  void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

  VkCommandBuffer beginSingleTimeCommands();
  void endSingleTimeCommands(VkCommandBuffer commandBuffer);
  void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);

  inline VkBuffer get_buffer_vertex(){return vertexBuffer;}
  inline VkBuffer get_buffer_index(){return indexBuffer;}
  inline vector<uint32_t> get_indices(){return indices;}

private:
  Engine_vulkan* engine_vulkan;
  VK_device* vk_device;

  VkBuffer vertexBuffer;
  VkDeviceMemory vertexBufferMemory;
  VkBuffer indexBuffer;
  VkDeviceMemory indexBufferMemory;

  std::vector<Vertex> vertices;
  std::vector<uint32_t> indices;
};

#endif
