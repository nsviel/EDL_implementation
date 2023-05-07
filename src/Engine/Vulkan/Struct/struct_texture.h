#ifndef STRUCT_TEXTURE_H
#define STRUCT_TEXTURE_H

#include "../../../common.h"


struct Struct_texture{
  VkImage textureImage;
  VkDeviceMemory textureImageMemory;
  VkImageView textureImageView;
  VkSampler textureSampler;
  VkDescriptorImageInfo imageInfo;
};


#endif
