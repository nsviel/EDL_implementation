#ifndef VK_TEXTURE_H
#define VK_TEXTURE_H

#include "../VK_struct.h"
#include "../../../common.h"

class Engine_vulkan;
class VK_device;
class VK_buffer;


class VK_texture
{
public:
  //Constructor / Destructor
  VK_texture(Engine_vulkan* engine_vulkan);
  ~VK_texture();

public:
  //Main functions
  void load_texture(string path);
  void cleanup();

  //Texture creation
  void create_texture_image(string path, VkImage& textureImage, VkDeviceMemory& textureImageMemory);
  void create_texture_image_view(VkImage& textureImage, VkImageView& textureImageView);
  void create_texture_sampler(VkSampler& textureSampler);

  //Generic image creation
  VkImageView create_image_view(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags);
  void create_image(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);
  void copy_buffer_to_image(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);

  inline VkDescriptorImageInfo get_image_info(){Struct_texture texture = *next(list_texture.begin(), 0); return texture.imageInfo;}

private:
  VK_device* vk_device;
  VK_buffer* vk_buffer;

  list<Struct_texture> list_texture;
};

#endif
