#ifndef STRUCT_RENDERPASS_H
#define STRUCT_RENDERPASS_H

#include "struct_frame.h"
#include "../../../common.h"


struct Struct_renderpass{
  //---------------------------

  //Function
  Frame_renderpass* get_current_frame(){return vec_frame[current_frame_ID];}

  //Info
  std::string name;

  //Renderpass stock images
  std::vector<Frame_renderpass*> vec_frame;
  uint32_t current_frame_ID = 0;

  //Render pass elements
  VkRenderPass renderpass;
  VkRenderPassCreateInfo renderpass_info;
  VkSubpassDescription subpass_description;
  VkSubpassDependency subpass_dependency;

  //Attachment
  VkAttachmentReference depth_ref;
  VkAttachmentReference color_ref;
  std::vector<VkAttachmentDescription> vec_attachment_description;

  //---------------------------
};


#endif
