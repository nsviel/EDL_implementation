#ifndef STRUCT_ATTACHMENT_H
#define STRUCT_ATTACHMENT_H

#include "../../../common.h"


struct Struct_subpass_attachment{
  //---------------------------

  int binding;

  //ATTACHMENT_LOADOP_CLEAR or ATTACHMENT_LOADOP_LOAD
  VkAttachmentLoadOp load_operation;
  VkAttachmentReference reference;

  //ATTACHMENT_LAYOUT_EMPTY or ATTACHMENT_LAYOUT_PRESENT
  VkImageLayout layout_initial;
  VkImageLayout layout_final;

  //---------------------------
};


#endif
