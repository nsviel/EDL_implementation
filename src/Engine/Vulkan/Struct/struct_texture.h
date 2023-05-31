#ifndef STRUCT_TEXTURE_H
#define STRUCT_TEXTURE_H

#include <string>
#include <vulkan/vulkan.h>


struct Struct_texture{
  //---------------------------

  std::string name;
  std::string path_texture;

  VkImage image;
  VkDeviceMemory mem;
  VkImageView view;
  VkSampler sampler;
  VkDescriptorImageInfo image_info;

  //---------------------------
};


#endif
