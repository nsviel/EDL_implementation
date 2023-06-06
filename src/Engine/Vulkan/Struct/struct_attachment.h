#ifndef STRUCT_ATTACHMENT_H
#define STRUCT_ATTACHMENT_H

#include "../../../common.h"


struct Struct_subpass_attachment{
  //---------------------------

  int binding;

  //ATTACHMENT_USAGE_CLEAR or ATTACHMENT_USAGE_CONSERVE
  VkAttachmentLoadOp usage;
  VkAttachmentReference reference;

  //ATTACHMENT_LAYOUT_EMPTY or ATTACHMENT_LAYOUT_PRESENT
  VkImageLayout layout_initial;
  VkImageLayout layout_final;

  //---------------------------
};


#endif
