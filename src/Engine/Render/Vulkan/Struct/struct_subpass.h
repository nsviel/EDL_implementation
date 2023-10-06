#ifndef STRUCT_SUBPASS_H
#define STRUCT_SUBPASS_H

#include <Specific/common.h>


struct Struct_subpass_attachment{
  //---------------------------

  int item;

  //Attachment info
  VkAttachmentLoadOp load_operation;
  VkAttachmentStoreOp store_operation;
  VkAttachmentReference reference;

  //Attachment image layout
  VkImageLayout layout_initial;
  VkImageLayout layout_final;

  //---------------------------
};

struct Struct_subpass{
  //---------------------------

  //Subpass info
  VkSubpassDescription description;
  VkSubpassDependency dependency;

  //Attachment
  Struct_subpass_attachment attached_color;
  Struct_subpass_attachment attached_depth;
  std::vector<VkAttachmentDescription> vec_attachment_description;

  //---------------------------
};


#endif
