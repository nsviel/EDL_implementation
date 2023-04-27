#ifndef VK_TEXTURE_H
#define VK_TEXTURE_H

#include "../../common.h"

#include <vulkan/vulkan.h>

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
  void create_texture_image();
  void create_texture_image_view();
  VkImageView create_image_view(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags);
  void create_texture_sampler();
  void create_image(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);
  void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);
  void cleanup();

  inline VkImageView get_textureImageView(){return textureImageView;}
  inline VkSampler get_textureSampler(){return textureSampler;}

private:
  VK_device* vk_device;
  VK_buffer* vk_buffer;

  VkImage textureImage;
  VkDeviceMemory textureImageMemory;
  VkImageView textureImageView;
  VkSampler textureSampler;
};

#endif
