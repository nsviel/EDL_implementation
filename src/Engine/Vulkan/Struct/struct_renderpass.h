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
  VkImageUsageFlags frame_usage;
  Frame* get_frame_current(){return vec_frame[frame_current_ID];}
  uint32_t frame_current_ID = 0;
  std::vector<Frame*> vec_frame;

  //Render pass elements
  VkRenderPass renderpass;
  VkCommandBuffer command_buffer;

  //Attachment
  std::vector<Struct_pipeline*> vec_pipeline;
  std::vector<Struct_subpass*> vec_subpass;

  //---------------------------
};


#endif
