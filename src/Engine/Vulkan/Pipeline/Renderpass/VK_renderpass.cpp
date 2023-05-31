#include "VK_renderpass.h"

#include "../Attachment/VK_depth.h"
#include "../Attachment/VK_color.h"

#include "../../VK_engine.h"
#include "../../VK_param.h"

//Manage fbo attachment (color / depth)


//Constructor / Destructor
VK_renderpass::VK_renderpass(VK_engine* vk_engine){
  //---------------------------

  this->vk_engine = vk_engine;
  this->vk_param = vk_engine->get_vk_param();
  this->vk_color = vk_engine->get_vk_color();

  //---------------------------
}
VK_renderpass::~VK_renderpass(){}

//Main function
void VK_renderpass::init_renderpass(){
  VK_depth* vk_depth = vk_engine->get_vk_depth();
  //---------------------------

  this->create_renderpass(&vk_param->renderpass_scene);
  this->create_renderpass(&vk_param->renderpass_canva);

  //---------------------------
}
void VK_renderpass::cleanup(){
  //---------------------------

  vkDestroyRenderPass(vk_param->device.device, vk_param->renderpass_scene.renderpass, nullptr);
  vkDestroyRenderPass(vk_param->device.device, vk_param->renderpass_canva.renderpass, nullptr);

  //---------------------------
}

//Subfunction
void VK_renderpass::create_renderpass(Struct_renderpass* renderpass){
  VK_depth* vk_depth = vk_engine->get_vk_depth();
  //---------------------------

  this->create_color_attachment(renderpass);
  this->create_depth_attachment(renderpass);
  this->create_subpass(renderpass);
  this->create_renderpass_info(renderpass);
  this->create_renderpass_obj(renderpass);

  //---------------------------
}
void VK_renderpass::create_depth_attachment(Struct_renderpass* renderpass){
  VK_depth* vk_depth = vk_engine->get_vk_depth();
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

  renderpass->depth_ref = depth_attachment_ref;
  renderpass->vec_attachment_description.push_back(depth_attachment);

  //---------------------------
}
void VK_renderpass::create_color_attachment(Struct_renderpass* renderpass){
  //---------------------------

  //Attachement description
  VkAttachmentDescription color_description{};
  color_description.format = vk_color->find_color_format();
  color_description.samples = VK_SAMPLE_COUNT_1_BIT;
  color_description.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
  color_description.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
  color_description.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
  color_description.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
  color_description.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
  color_description.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

  //Attachment references
  VkAttachmentReference color_reference{};
  color_reference.attachment = 0;
  color_reference.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

  renderpass->color_ref = color_reference;
  renderpass->vec_attachment_description.push_back(color_description);

  //---------------------------
}
void VK_renderpass::create_subpass(Struct_renderpass* renderpass){
  //---------------------------

  //Subpasses
  VkSubpassDescription subpass_description{};
  subpass_description.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
  subpass_description.colorAttachmentCount = 1;
  subpass_description.pColorAttachments = &renderpass->color_ref;
  subpass_description.pDepthStencilAttachment = &renderpass->depth_ref;

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
void VK_renderpass::create_renderpass_obj(Struct_renderpass* renderpass){
  //---------------------------

  //Render pass creation
  VkResult result = vkCreateRenderPass(vk_param->device.device, &renderpass->renderpass_info, nullptr, &renderpass->renderpass);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to create render pass!");
  }

  //---------------------------
}
