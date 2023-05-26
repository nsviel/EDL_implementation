#include "VK_renderpass.h"

#include "../Engine.h"
#include "../Param_vulkan.h"
#include "../Device/VK_device.h"
#include "../Swapchain/VK_swapchain.h"
#include "../Swapchain/VK_image.h"
#include "../Attachment/VK_depth.h"
#include "../Attachment/VK_color.h"

//Manage fbo attachment (color / depth)


//Constructor / Destructor
VK_renderpass::VK_renderpass(Engine* engineManager){
  //---------------------------

  this->engineManager = engineManager;
  this->param_vulkan = engineManager->get_param_vulkan();
  this->vk_device = engineManager->get_vk_device();
  this->vk_swapchain = engineManager->get_vk_swapchain();
  this->vk_image = engineManager->get_vk_image();
  this->vk_color = engineManager->get_vk_color();

  //---------------------------
}
VK_renderpass::~VK_renderpass(){}

//Main function
void VK_renderpass::init_renderpass(){
  VK_depth* vk_depth = engineManager->get_vk_depth();
  //---------------------------

  this->renderpass = new Struct_renderpass();
  this->create_color_attachment(renderpass);
  this->create_depth_attachment(renderpass);
  this->create_subpass(renderpass);
  this->create_renderpass_info(renderpass);
  this->create_renderpass(renderpass);

  //---------------------------
}
void VK_renderpass::cleanup(){
  //---------------------------

  vkDestroyRenderPass(param_vulkan->device.device, renderpass->renderpass, nullptr);

  //---------------------------
}

//Subfunction
void VK_renderpass::create_depth_attachment(Struct_renderpass* renderpass){
  VK_depth* vk_depth = engineManager->get_vk_depth();
  //---------------------------

  VkAttachmentDescription depth_attachment{};
  depth_attachment.format = vk_depth->find_depth_format();
  depth_attachment.samples = VK_SAMPLE_COUNT_1_BIT;
  depth_attachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
  depth_attachment.storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
  depth_attachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
  depth_attachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
  depth_attachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
  depth_attachment.finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

  VkAttachmentReference depth_attachment_ref{};
  depth_attachment_ref.attachment = 1;
  depth_attachment_ref.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

  renderpass->depth_attachment = depth_attachment;
  renderpass->depth_attachment_ref = depth_attachment_ref;

  renderpass->vec_attachment_description.push_back(depth_attachment);
  renderpass->vec_attachment_reference.push_back(depth_attachment_ref);

  //---------------------------
}
void VK_renderpass::create_color_attachment(Struct_renderpass* renderpass){
  //---------------------------

  //Attachement description
  VkAttachmentDescription color_attachment{};
  color_attachment.format = vk_color->find_color_format();
  color_attachment.samples = VK_SAMPLE_COUNT_1_BIT;
  color_attachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
  color_attachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
  color_attachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
  color_attachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
  color_attachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
  color_attachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

  //Attachment references
  VkAttachmentReference color_attachment_ref{};
  color_attachment_ref.attachment = 0;
  color_attachment_ref.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

  renderpass->color_attachment = color_attachment;
  renderpass->color_attachment_ref = color_attachment_ref;

  renderpass->vec_attachment_description.push_back(color_attachment);
  renderpass->vec_attachment_reference.push_back(color_attachment_ref);

  //---------------------------
}
void VK_renderpass::create_subpass(Struct_renderpass* renderpass){
  //---------------------------

  //Subpasses
  VkSubpassDescription subpass_description{};
  subpass_description.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
  subpass_description.colorAttachmentCount = 1;
  subpass_description.pColorAttachments = &renderpass->color_attachment_ref;
  subpass_description.pDepthStencilAttachment = &renderpass->depth_attachment_ref;

  VkSubpassDependency subpass_dependency{};
  subpass_dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
  subpass_dependency.dstSubpass = 0;
  subpass_dependency.srcAccessMask = 0;
  subpass_dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
  subpass_dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
  subpass_dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;

  //---------------------------
  renderpass->subpass_description = subpass_description;
  renderpass->subpass_dependency = subpass_dependency;
}
void VK_renderpass::create_renderpass_info(Struct_renderpass* renderpass){
  //---------------------------

  VkRenderPassCreateInfo renderpass_info{};
  renderpass_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
  renderpass_info.attachmentCount = static_cast<uint32_t>(renderpass->vec_attachment_description.size());
  renderpass_info.pAttachments = renderpass->vec_attachment_description.data();
  renderpass_info.subpassCount = 1;
  renderpass_info.pSubpasses = &renderpass->subpass_description;
  renderpass_info.dependencyCount = 1;
  renderpass_info.pDependencies = &renderpass->subpass_dependency;

  //---------------------------
  renderpass->renderpass_info = renderpass_info;
}
void VK_renderpass::create_renderpass(Struct_renderpass* renderpass){
  //---------------------------

  //Render pass creation
  VkResult result = vkCreateRenderPass(param_vulkan->device.device, &renderpass->renderpass_info, nullptr, &renderpass->renderpass);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to create render pass!");
  }

  //---------------------------
}
