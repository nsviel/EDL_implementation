#include "VK_renderpass.h"
#include "VK_subpass.h"

#include "Init/RP_scene.h"
#include "Init/RP_render.h"
#include "Init/RP_ui.h"

#include "../Command/VK_command.h"
#include "../Pipeline/VK_pipeline.h"

#include "../../VK_engine.h"
#include "../../VK_param.h"
#include "../../Presentation/Swapchain/VK_frame.h"
#include "../../Presentation/Swapchain/VK_framebuffer.h"
#include "../../Presentation/Image/VK_color.h"
#include "../../Presentation/Image/VK_depth.h"


//Constructor / Destructor
VK_renderpass::VK_renderpass(VK_engine* vk_engine){
  //---------------------------

  this->vk_engine = vk_engine;
  this->vk_param = vk_engine->get_vk_param();
  this->vk_color = vk_engine->get_vk_color();
  this->vk_pipeline = vk_engine->get_vk_pipeline();
  this->vk_subpass = new VK_subpass(vk_engine);

  this->rp_scene = new RP_scene(vk_engine);
  this->rp_render = new RP_render(vk_engine);
  this->rp_ui = new RP_ui(vk_engine);

  //---------------------------
}
VK_renderpass::~VK_renderpass(){
  //---------------------------

  delete vk_subpass;

  //---------------------------
}

//Main function
void VK_renderpass::init_renderpass(){
  //---------------------------

  rp_scene->init_renderpass_scene(&vk_param->renderpass_scene);
  rp_render->init_renderpass_render(&vk_param->renderpass_render);
  rp_ui->init_renderpass_ui(&vk_param->renderpass_ui);

  //---------------------------
}
void VK_renderpass::clean_renderpass(){
  VK_frame* vk_frame = vk_engine->get_vk_frame();
  //---------------------------

  vk_frame->clean_frame_renderpass(&vk_param->renderpass_scene);
  vk_frame->clean_frame_renderpass(&vk_param->renderpass_render);
  vk_frame->clean_frame_renderpass(&vk_param->renderpass_ui);

  this->clean_renderpass_object(&vk_param->renderpass_scene);
  this->clean_renderpass_object(&vk_param->renderpass_render);
  this->clean_renderpass_object(&vk_param->renderpass_ui);

  //---------------------------
}
void VK_renderpass::clean_renderpass_object(Struct_renderpass* renderpass){
  //---------------------------

  vkDestroyRenderPass(vk_param->device.device, renderpass->renderpass, nullptr);
  vk_pipeline->clean_pipeline(renderpass);

  //---------------------------
}

//Subfunction
void VK_renderpass::create_renderpass(Struct_renderpass* renderpass){
  VK_command* vk_command = vk_engine->get_vk_command();
  VK_frame* vk_frame = vk_engine->get_vk_frame();
  //---------------------------

  this->create_color_attachment(renderpass);
  this->create_depth_attachment(renderpass);
  this->create_subpass(renderpass->vec_subpass[0]);
  this->create_renderpass_obj(renderpass);
  vk_command->allocate_command_buffer(renderpass);
  vk_pipeline->create_pipeline(renderpass);
  vk_frame->create_frame_renderpass(renderpass);

  //---------------------------
}
void VK_renderpass::create_color_attachment(Struct_renderpass* renderpass){
  //---------------------------

  //Attachement description
  VkAttachmentDescription color_description{};
  color_description.format = vk_color->find_color_format();
  color_description.samples = VK_SAMPLE_COUNT_1_BIT;
  color_description.loadOp = renderpass->vec_subpass[0]->color.attachment_usage;
  color_description.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
  color_description.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
  color_description.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
  color_description.initialLayout = renderpass->vec_subpass[0]->color.layout_initial;
  color_description.finalLayout = renderpass->vec_subpass[0]->color.layout_final;

  //Attachment references
  VkAttachmentReference color_reference{};
  color_reference.attachment = renderpass->vec_subpass[0]->color.binding;
  color_reference.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

  renderpass->vec_subpass[0]->color.reference = color_reference;
  renderpass->vec_subpass[0]->vec_attachment_description.push_back(color_description);

  //---------------------------
}
void VK_renderpass::create_depth_attachment(Struct_renderpass* renderpass){
  VK_depth* vk_depth = vk_engine->get_vk_depth();
  //---------------------------

  VkAttachmentDescription depth_attachment{};
  depth_attachment.format = vk_depth->find_depth_format();
  depth_attachment.samples = VK_SAMPLE_COUNT_1_BIT;
  depth_attachment.loadOp = renderpass->vec_subpass[0]->depth.attachment_usage;
  depth_attachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
  depth_attachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
  depth_attachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
  depth_attachment.initialLayout = renderpass->vec_subpass[0]->depth.layout_initial;
  depth_attachment.finalLayout = renderpass->vec_subpass[0]->depth.layout_final;

  VkAttachmentReference depth_attachment_ref{};
  depth_attachment_ref.attachment = renderpass->vec_subpass[0]->depth.binding;
  depth_attachment_ref.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

  renderpass->vec_subpass[0]->depth.reference = depth_attachment_ref;
  renderpass->vec_subpass[0]->vec_attachment_description.push_back(depth_attachment);

  //---------------------------
}
void VK_renderpass::create_subpass(Struct_subpass* subpass){
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
void VK_renderpass::create_renderpass_obj(Struct_renderpass* renderpass){
  //---------------------------

  VkRenderPassCreateInfo renderpass_info{};
  renderpass_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
  renderpass_info.attachmentCount = static_cast<uint32_t>(renderpass->vec_subpass[0]->vec_attachment_description.size());
  renderpass_info.pAttachments = renderpass->vec_subpass[0]->vec_attachment_description.data();
  renderpass_info.subpassCount = 1;
  renderpass_info.pSubpasses = &renderpass->vec_subpass[0]->description;
  renderpass_info.dependencyCount = 1;
  renderpass_info.pDependencies = &renderpass->vec_subpass[0]->dependency;

  //Render pass creation
  VkResult result = vkCreateRenderPass(vk_param->device.device, &renderpass_info, nullptr, &renderpass->renderpass);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to create render pass!");
  }

  //---------------------------
}
