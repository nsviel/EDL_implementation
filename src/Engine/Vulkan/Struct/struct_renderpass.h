#ifndef STRUCT_RENDERPASS_H
#define STRUCT_RENDERPASS_H

#include "struct_frame.h"
#include "../../../common.h"


struct Struct_renderpass{
  //---------------------------

  //Info
  std::string name;

  //Render pass elements
  VkRenderPass renderpass;
  VkRenderPassCreateInfo renderpass_info;
  VkSubpassDescription subpass_description;
  VkSubpassDependency subpass_dependency;
  std::vector<Frame_swapchain*> vec_frame_render;

  //Attachment
  VkAttachmentReference depth_ref;
  VkAttachmentReference color_ref;
  std::vector<VkAttachmentDescription> vec_attachment_description;

  //---------------------------
};


#endif
