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

  VkAttachmentDescription depth_attachment;
  VkAttachmentReference depth_attachment_ref;
  VkAttachmentDescription color_attachment;
  VkAttachmentReference color_attachment_ref;

  std::vector<VkAttachmentDescription> vec_attachment_description;
  std::vector<VkAttachmentReference> vec_attachment_reference;
};


#endif
