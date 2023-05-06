#ifndef VK_BUFFER_H
#define VK_BUFFER_H

#include "../VK_struct.h"
#include "../../../common.h"

class Engine;
class VK_device;
class VK_descriptor;


class VK_buffer
{
public:
  //Constructor / Destructor
  VK_buffer(Engine* engineManager);
  ~VK_buffer();

public:
  //Main functions
  void insert_cloud_in_engine(Cloud* cloud);
  void cleanup(Cloud* cloud);

  //Data buffer functions
  void create_buffer_uv(Cloud* cloud, std::vector<vec2> vertices);
  void create_buffer_xyz(Cloud* cloud, std::vector<vec3> vertices);
  void create_buffer_rgb(Cloud* cloud, std::vector<vec4> vertices);

  //Buffer functions
  void bind_buffer_memory(VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
  void create_buffer(VkDeviceSize size, VkBufferUsageFlags usage, VkBuffer& buffer);
  void copy_buffer_to_gpu(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

  //Specific functions
  uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
  void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);

private:
  Engine* engineManager;
  VK_device* vk_device;
  VK_descriptor* vk_descriptor;

  VkDeviceMemory dev_memory;
};

#endif
