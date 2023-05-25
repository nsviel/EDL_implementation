#ifndef STRUCT_FRAMEBUFFER_H
#define STRUCT_FRAMEBUFFER_H

#include "../../../common.h"


struct Struct_attachment{
  std::string name;

  VkImage image;
  VkImageView view;
  VkDeviceMemory mem;
  VkFormat format;
};


#endif
