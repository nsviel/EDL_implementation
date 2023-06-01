#ifndef STRUCT_RENDERPASS_H
#define STRUCT_RENDERPASS_H

#include "struct_frame.h"
#include "struct_attachment.h"
#include "../../../common.h"


struct Struct_renderpass{
  //---------------------------

  //Function
  Frame* get_frame_inflight(){return vec_frame[frame_inflight_ID];}
  Frame* get_frame_swapchain(){return vec_frame[frame_sawpchain_ID];}

  //Info
  std::string name;

  //Renderpass stock images
  std::vector<Frame*> vec_frame;
  uint32_t frame_sawpchain_ID = 0;
  uint32_t frame_inflight_ID = 0;

  //Render pass elements
  VkRenderPass renderpass;
  VkRenderPassCreateInfo renderpass_info;
  VkSubpassDescription subpass_description;
  VkSubpassDependency subpass_dependency;

  //Attachment
  VkAttachmentReference depth_ref;
  VkAttachmentReference color_ref;
  Struct_attachment_usage attachment;
  std::vector<VkAttachmentDescription> vec_attachment_description;

  //---------------------------
};


#endif
