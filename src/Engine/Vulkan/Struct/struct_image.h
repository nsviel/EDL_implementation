#ifndef STRUCT_TEXTURE_H
#define STRUCT_TEXTURE_H

#include <string>
#include <vulkan/vulkan.h>


struct Struct_image{
  //---------------------------

  std::string name;

  uint32_t width;
  uint32_t height;

  VkImage image;
  VkImageView view;
  VkImageTiling tiling;
  VkImageUsageFlags usage;
  VkImageAspectFlags aspect;

  VkFormat format;
  VkDeviceMemory mem;
  VkMemoryPropertyFlags properties;

  //---------------------------
};

struct Struct_texture{
  //---------------------------

  std::string name;
  std::string path_texture;

  Struct_image image;
  VkSampler sampler;

  //---------------------------
};


#endif
