#ifndef VK_BUFFER_H
#define VK_BUFFER_H

#include "../VK_struct.h"
#include "../../../common.h"

class Engine_vulkan;
class VK_device;
class VK_descriptor;


class VK_buffer
{
public:
  //Constructor / Destructor
  VK_buffer(Engine_vulkan* engine_vulkan);
  ~VK_buffer();

public:
  //Main functions
  void insert_cloud_in_engine(Cloud* cloud);
  void insert_model_in_engine(std::vector<Vertex> vertices, std::string tex_path);
  void cleanup(Cloud* cloud);

  //Buffer functions
  void create_buffer_data(std::vector<Vertex> vertices);
  void create_buffer_uv(Cloud* cloud, std::vector<vec2> vertices);
  void create_buffer_xyz(Cloud* cloud, std::vector<vec3> vertices);
  void create_buffer_rgb(Cloud* cloud, std::vector<vec4> vertices);

  void bind_buffer_memory(VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
  void create_buffer(VkDeviceSize size, VkBufferUsageFlags usage, VkBuffer& buffer);
  void copy_buffer_to_gpu(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

  //Specific functions
  uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
  void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);

private:
  Engine_vulkan* engine_vulkan;
  VK_device* vk_device;
  VK_descriptor* vk_descriptor;

  VkDeviceMemory dev_memory;
};

#endif
