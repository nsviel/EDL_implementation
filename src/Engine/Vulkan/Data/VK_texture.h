#ifndef VK_TEXTURE_H
#define VK_TEXTURE_H

#include "../Struct/struct_texture.h"
#include "../../../common.h"

class Engine;
class Param_vulkan;
class VK_device;
class VK_buffer;
class VK_physical_device;


class VK_texture
{
public:
  //Constructor / Destructor
  VK_texture(Engine* engineManager);
  ~VK_texture();

public:
  //Main functions
  void load_texture(Object* object);
  void cleanup_texture(Object* object);

  //Texture creation
  void create_texture_image(string path, VkImage& textureImage, VkDeviceMemory& textureImageMemory);
  void create_texture_image_view(VkImage& textureImage, VkImageView& textureImageView);
  void create_texture_sampler(VkSampler& textureSampler);

  //Generic image creation
  VkImageView create_image_view(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags);
  void create_image(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);
  void copy_buffer_to_image(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);

private:
  Engine* engineManager;
  Param_vulkan* param_vulkan;
  VK_device* vk_device;
  VK_buffer* vk_buffer;
  VK_physical_device* vk_physical_device;
};

#endif
