#ifndef STRUCT_RENDERPASS_H
#define STRUCT_RENDERPASS_H

#include "struct_frame.h"
#include "struct_attachment.h"
#include "struct_pipeline.h"
#include "../../../common.h"


struct Struct_subpass{
  //---------------------------

  //Subpass info
  VkSubpassDescription description;
  VkSubpassDependency dependency;

  //Attachment
  Struct_subpass_attachment color;
  Struct_subpass_attachment depth;
  std::vector<VkAttachmentDescription> vec_attachment_description;

  //---------------------------
};

struct Struct_renderpass{
  //---------------------------

  //Info
  std::string name;

  //Renderpass frame set
  Frame_set* frame_set;
  VkImageUsageFlags frame_usage;

  //Render pass elements
  VkRenderPass renderpass;
  VkCommandBuffer command_buffer;

  //Attachment
  std::vector<Struct_pipeline*> vec_pipeline;
  std::vector<Struct_subpass*> vec_subpass;

  //---------------------------
};


#endif
