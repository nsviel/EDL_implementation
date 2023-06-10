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
  uint32_t width;
  uint32_t height;

  //Image info
  VkImage image;
  VkImageView view;
  VkImageTiling tiling;
  VkImageUsageFlags image_usage;
  VkImageAspectFlags aspect;
  VkImageLayout layout;

  //Other info
  VkFormat format;
  VkDeviceMemory mem;
  VkMemoryPropertyFlags properties;
  VkSampler sampler;

  //---------------------------
};


#endif
