#ifndef STRUCT_RENDERPASS_H
#define STRUCT_RENDERPASS_H

#include <string>
#include <vector>
#include <vulkan/vulkan.h>


struct Struct_renderpass{
  //Info
  std::string name;

  //Render pass elements
  VkRenderPass renderpass;
  VkRenderPassCreateInfo renderpass_info;
  VkSubpassDescription subpass_description;
  VkSubpassDependency subpass_dependency;

  //Attachment
  VkAttachmentReference depth_ref;
  VkAttachmentReference color_ref;
  std::vector<VkAttachmentDescription> vec_attachment_description;
};


#endif
