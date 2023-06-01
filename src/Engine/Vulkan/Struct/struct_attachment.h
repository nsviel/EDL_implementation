#ifndef STRUCT_ATTACHMENT_H
#define STRUCT_ATTACHMENT_H

#include "../../../common.h"


struct Struct_attachment_usage{
  //---------------------------

  //ATTACHMENT_USAGE_CLEAR or ATTACHMENT_USAGE_CONSERVE
  VkAttachmentLoadOp usage;

  //ATTACHMENT_LAYOUT_EMPTY or ATTACHMENT_LAYOUT_PRESENT
  VkImageLayout layout_initial;
  VkImageLayout layout_final;

  //---------------------------
};

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
