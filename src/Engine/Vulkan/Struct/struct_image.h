#ifndef STRUCT_TEXTURE_H
#define STRUCT_TEXTURE_H

#include <string>
#include <vulkan/vulkan.h>


struct Struct_image{
  //---------------------------

  //General info
  std::string name;
  std::string path;

  //Dimension
  uint32_t width = 0;
  uint32_t height = 0;
  uint32_t mip_level_max = 1;
  uint32_t mip_level = 1;

  //Image info
  VkImage image;
  VkImageView view;
  VkImageTiling tiling;
  VkImageUsageFlags image_usage;
  VkImageAspectFlags aspect;
  VkImageLayout sampler_layout;

  //Other info
  VkFormat format;
  VkDeviceMemory mem;
  VkMemoryPropertyFlags properties;
  VkSampler sampler;

  //---------------------------
};


#endif
