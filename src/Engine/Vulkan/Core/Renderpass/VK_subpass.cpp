#include "VK_subpass.h"

#include "../../VK_engine.h"
#include "../../VK_param.h"

#include "../../Presentation/Image/VK_color.h"
#include "../../Presentation/Image/VK_depth.h"


//Constructor / Destructor
VK_subpass::VK_subpass(VK_engine* vk_engine){
  //---------------------------

  this->vk_engine = vk_engine;
  this->vk_param = vk_engine->get_vk_param();
  this->vk_color = vk_engine->get_vk_color();

  //---------------------------
}
VK_subpass::~VK_subpass(){}

//Main function
void VK_subpass::create_subpass(Struct_renderpass* renderpass){
  //---------------------------

  for(int i=0; i<renderpass->vec_subpass.size(); i++){
    Struct_subpass* subpass = renderpass->vec_subpass[i];
    this->create_color_attachment(subpass);
    this->create_depth_attachment(subpass);
    this->create_subpass_description(subpass);
  }

  //---------------------------
}

//Subfunction
void VK_subpass::create_color_attachment(Struct_subpass* subpass){
  //---------------------------

  //Attachement description
  VkAttachmentDescription color_description{};
  color_description.format = vk_color->find_color_format();
  color_description.samples = VK_SAMPLE_COUNT_1_BIT;
  color_description.loadOp = subpass->color.load_operation;
  color_description.storeOp = subpass->color.store_operation;
  color_description.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
  color_description.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
  color_description.initialLayout = subpass->color.layout_initial;
  color_description.finalLayout = subpass->color.layout_final;

  //Attachment references
  VkAttachmentReference color_reference{};
  color_reference.attachment = subpass->color.binding;
  color_reference.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

  subpass->color.reference = color_reference;
  subpass->vec_attachment_description.push_back(color_description);

  //---------------------------
}
void VK_subpass::create_depth_attachment(Struct_subpass* subpass){
  VK_depth* vk_depth = vk_engine->get_vk_depth();
  //---------------------------

  VkAttachmentDescription depth_attachment{};
  depth_attachment.format = vk_depth->find_depth_format();
  depth_attachment.samples = VK_SAMPLE_COUNT_1_BIT;
  depth_attachment.loadOp = subpass->depth.load_operation;
  depth_attachment.storeOp = subpass->depth.store_operation;
  depth_attachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
  depth_attachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
  depth_attachment.initialLayout = subpass->depth.layout_initial;
  depth_attachment.finalLayout = subpass->depth.layout_final;

  VkAttachmentReference depth_attachment_ref{};
  depth_attachment_ref.attachment = subpass->depth.binding;
  depth_attachment_ref.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

  subpass->depth.reference = depth_attachment_ref;
  subpass->vec_attachment_description.push_back(depth_attachment);

  //---------------------------
}
void VK_subpass::create_subpass_description(Struct_subpass* subpass){
  //---------------------------

  //Subpasses
  VkSubpassDescription subpass_description{};
  subpass_description.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
  subpass_description.colorAttachmentCount = 1;
  subpass_description.pColorAttachments = &subpass->color.reference;
  subpass_description.pDepthStencilAttachment = &subpass->depth.reference;

  VkSubpassDependency subpass_dependency{};
  subpass_dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
  subpass_dependency.dstSubpass = 0;
  subpass_dependency.srcAccessMask = 0;
  subpass_dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
  subpass_dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
  subpass_dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;

  //---------------------------
  subpass->description = subpass_description;
  subpass->dependency = subpass_dependency;
}
