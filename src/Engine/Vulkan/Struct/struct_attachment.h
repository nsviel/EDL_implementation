#ifndef STRUCT_ATTACHMENT_H
#define STRUCT_ATTACHMENT_H

#include "../../../common.h"


struct Struct_attachment_usage{
  //---------------------------

  //ATTACHMENT_USAGE_CLEAR or ATTACHMENT_USAGE_CONSERVE
  VkAttachmentLoadOp usage;

  //ATTACHMENT_LAYOUT_EMPTY or ATTACHMENT_LAYOUT_PRESENT
  VkImageLayout color_layout_initial;
  VkImageLayout color_layout_final;
  VkImageLayout depth_layout_initial;
  VkImageLayout depth_layout_final;

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
