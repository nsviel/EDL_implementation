#ifndef STRUCT_TEXTURE_H
#define STRUCT_TEXTURE_H

#include <string>
#include <vulkan/vulkan.h>


struct Struct_texture{
  //---------------------------

  std::string path_texture;

  VkImage textureImage;
  VkDeviceMemory textureImageMemory;
  VkImageView textureImageView;
  VkSampler textureSampler;
  VkDescriptorImageInfo imageInfo;

  //---------------------------
};


#endif
