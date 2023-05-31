#ifndef STRUCT_ATTACHMENT_H
#define STRUCT_ATTACHMENT_H

#include "../../../common.h"


struct Struct_attachment{
  //---------------------------

  std::string name;

  VkImage image;
  VkImageView view;
  VkDeviceMemory mem;
  VkFormat format;

  //---------------------------
};


#endif
