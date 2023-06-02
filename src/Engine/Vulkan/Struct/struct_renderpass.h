#ifndef STRUCT_RENDERPASS_H
#define STRUCT_RENDERPASS_H

#include "struct_frame.h"
#include "struct_attachment.h"
#include "struct_pipeline.h"
#include "../../../common.h"


struct Struct_renderpass{
  //---------------------------

  //Info
  std::string name;

  //Renderpass frame set
  Frame_set* frame_set;

  //Render pass elements
  VkRenderPass renderpass;
  VkRenderPassCreateInfo renderpass_info;
  VkSubpassDescription subpass_description;
  VkSubpassDependency subpass_dependency;
  Struct_pipeline* pipeline;

  //Attachment
  VkAttachmentReference depth_ref;
  VkAttachmentReference color_ref;
  Struct_attachment_usage* attachment;
  std::vector<VkAttachmentDescription> vec_attachment_description;

  //---------------------------
};


#endif
