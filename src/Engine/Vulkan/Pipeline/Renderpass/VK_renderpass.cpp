#include "VK_renderpass.h"

#include "../Command/VK_command.h"
#include "../Pipeline/VK_pipeline.h"
#include "../Attachment/VK_color.h"
#include "../Attachment/VK_depth.h"

#include "../../VK_engine.h"
#include "../../VK_param.h"
#include "../../Presentation/Swapchain/VK_frame.h"

//Manage fbo attachment (color / depth)


//Constructor / Destructor
VK_renderpass::VK_renderpass(VK_engine* vk_engine){
  //---------------------------

  this->vk_engine = vk_engine;
  this->vk_param = vk_engine->get_vk_param();
  this->vk_color = vk_engine->get_vk_color();
  this->vk_pipeline = vk_engine->get_vk_pipeline();

  //---------------------------
}
VK_renderpass::~VK_renderpass(){}

//Main function
void VK_renderpass::init_renderpass(){
  //---------------------------

  this->init_renderpass_scene();
  this->init_renderpass_glyph();
  this->init_renderpass_canvas();
  this->init_renderpass_gui();

  //---------------------------
}
void VK_renderpass::clean_renderpass(){
  //---------------------------

  this->clean_renderpass_object(&vk_param->renderpass_scene);
  this->clean_renderpass_object(&vk_param->renderpass_glyph);
  this->clean_renderpass_object(&vk_param->renderpass_canvas);
  this->clean_renderpass_object(&vk_param->renderpass_gui);

  //---------------------------
}
void VK_renderpass::clean_renderpass_object(Struct_renderpass* renderpass){
  VK_frame* vk_frame = vk_engine->get_vk_frame();
  //---------------------------

  vk_frame->clean_frame_renderpass(renderpass);
  vkDestroyRenderPass(vk_param->device.device, renderpass->renderpass, nullptr);
  vk_pipeline->clean_pipeline(renderpass->pipeline);

  //---------------------------
}

//Render pass objects
void VK_renderpass::init_renderpass_scene(){
  //---------------------------

  //Render pass
  Struct_renderpass* renderpass = &vk_param->renderpass_scene;
  renderpass->name = "scene";

  //Attachment
  renderpass->subpass_0.color.binding = 0;
  renderpass->subpass_0.color.usage = ATTACHMENT_USAGE_CLEAR;
  renderpass->subpass_0.color.layout_initial = IMAGE_LAYOUT_EMPTY;
  renderpass->subpass_0.color.layout_final = IMAGE_LAYOUT_PRESENT;

  renderpass->subpass_0.depth.binding = 1;
  renderpass->subpass_0.depth.usage = ATTACHMENT_USAGE_CLEAR;
  renderpass->subpass_0.depth.layout_initial = IMAGE_LAYOUT_EMPTY;
  renderpass->subpass_0.depth.layout_final = IMAGE_LAYOUT_DEPTH;
  this->create_renderpass(renderpass);

  //Pipeline
  renderpass->pipeline = new Struct_pipeline();
  renderpass->pipeline->name = "scene";
  renderpass->pipeline->topology = "point";
  renderpass->pipeline->compile_shader = true;
  renderpass->pipeline->path_shader_vs = "Base/shader_scene_vs";
  renderpass->pipeline->path_shader_fs = "Base/shader_scene_fs";
  renderpass->pipeline->vec_data_name.push_back("location");
  renderpass->pipeline->vec_data_name.push_back("color");
  renderpass->pipeline->binding.vec_required_binding.push_back(std::make_tuple("mvp", "mat4", 0, TYPE_UNIFORM, STAGE_VS));
  vk_pipeline->create_pipeline(renderpass);

  //---------------------------
}
void VK_renderpass::init_renderpass_glyph(){
  //---------------------------

  //Render pass
  Struct_renderpass* renderpass = &vk_param->renderpass_glyph;
  renderpass->name = "glyph";

  //Attachment
  renderpass->subpass_0.color.binding = 0;
  renderpass->subpass_0.color.usage = ATTACHMENT_USAGE_CLEAR;
  renderpass->subpass_0.color.layout_initial = IMAGE_LAYOUT_EMPTY;
  renderpass->subpass_0.color.layout_final = IMAGE_LAYOUT_PRESENT;

  renderpass->subpass_0.depth.binding = 1;
  renderpass->subpass_0.depth.usage = ATTACHMENT_USAGE_CLEAR;
  renderpass->subpass_0.depth.layout_initial = IMAGE_LAYOUT_EMPTY;
  renderpass->subpass_0.depth.layout_final = IMAGE_LAYOUT_DEPTH;
  this->create_renderpass(renderpass);

  //Pipeline
  renderpass->pipeline = new Struct_pipeline();
  renderpass->pipeline->name = "glyph";
  renderpass->pipeline->topology = "line";
  renderpass->pipeline->compile_shader = true;
  renderpass->pipeline->path_shader_vs = "Base/shader_glyph_vs";
  renderpass->pipeline->path_shader_fs = "Base/shader_glyph_fs";
  renderpass->pipeline->vec_data_name.push_back("location");
  renderpass->pipeline->vec_data_name.push_back("color");
  renderpass->pipeline->binding.vec_required_binding.push_back(std::make_tuple("mvp", "mat4", 0, TYPE_UNIFORM, STAGE_VS));
  vk_pipeline->create_pipeline(renderpass);

  //---------------------------
}
void VK_renderpass::init_renderpass_canvas(){
  //---------------------------

  //Render pass
  Struct_renderpass* renderpass = &vk_param->renderpass_canvas;
  renderpass->name = "canvas";

  //Attachment
  renderpass->subpass_0.color.binding = 0;
  renderpass->subpass_0.color.usage = ATTACHMENT_USAGE_CLEAR;
  renderpass->subpass_0.color.layout_initial = IMAGE_LAYOUT_EMPTY;
  renderpass->subpass_0.color.layout_final = IMAGE_LAYOUT_PRESENT;

  renderpass->subpass_0.depth.binding = 1;
  renderpass->subpass_0.depth.usage = ATTACHMENT_USAGE_CLEAR;
  renderpass->subpass_0.depth.layout_initial = IMAGE_LAYOUT_EMPTY;
  renderpass->subpass_0.depth.layout_final = IMAGE_LAYOUT_DEPTH;
  this->create_renderpass(renderpass);

  //Pipeline
  renderpass->pipeline = new Struct_pipeline();
  renderpass->pipeline->name = "canvas";
  renderpass->pipeline->topology = "triangle";
  renderpass->pipeline->compile_shader = true;
  renderpass->pipeline->path_shader_vs = "Base/shader_canvas_vs";
  renderpass->pipeline->path_shader_fs = "Base/shader_canvas_fs";
  renderpass->pipeline->vec_data_name.push_back("location");
  renderpass->pipeline->vec_data_name.push_back("tex_coord");
  renderpass->pipeline->binding.vec_required_binding.push_back(std::make_tuple("mvp", "mat4", 0, TYPE_UNIFORM, STAGE_VS));
  renderpass->pipeline->binding.vec_required_binding.push_back(std::make_tuple("texture", "", 1, TYPE_SAMPLER, STAGE_FS));
  vk_pipeline->create_pipeline(renderpass);

  //---------------------------
}
void VK_renderpass::init_renderpass_gui(){
  //---------------------------

  //Render pass
  Struct_renderpass* renderpass = &vk_param->renderpass_gui;
  renderpass->name = "gui";

  //Attachment
  renderpass->subpass_0.color.binding = 0;
  renderpass->subpass_0.color.usage = ATTACHMENT_USAGE_CLEAR;
  renderpass->subpass_0.color.layout_initial = IMAGE_LAYOUT_PRESENT;
  renderpass->subpass_0.color.layout_final = IMAGE_LAYOUT_PRESENT;

  renderpass->subpass_0.depth.binding = 1;
  renderpass->subpass_0.depth.usage = ATTACHMENT_USAGE_CLEAR;
  renderpass->subpass_0.depth.layout_initial = IMAGE_LAYOUT_DEPTH;
  renderpass->subpass_0.depth.layout_final = IMAGE_LAYOUT_DEPTH;



  this->create_renderpass(renderpass);

  //Pipeline
  renderpass->pipeline = new Struct_pipeline();
  renderpass->pipeline->name = "gui";
  renderpass->pipeline->topology = "line";
  renderpass->pipeline->compile_shader = true;
  renderpass->pipeline->path_shader_vs = "Base/shader_scene_vs";
  renderpass->pipeline->path_shader_fs = "Base/shader_scene_fs";
  renderpass->pipeline->vec_data_name.push_back("location");
  renderpass->pipeline->vec_data_name.push_back("color");
  renderpass->pipeline->binding.vec_required_binding.push_back(std::make_tuple("mvp", "mat4", 0, TYPE_UNIFORM, STAGE_VS));
  vk_pipeline->create_pipeline(renderpass);

  //---------------------------
}

//Subfunction
void VK_renderpass::create_renderpass(Struct_renderpass* renderpass){
  VK_frame* vk_frame = vk_engine->get_vk_frame();
  VK_command* vk_command = vk_engine->get_vk_command();
  //---------------------------

  this->create_color_attachment(renderpass);
  this->create_depth_attachment(renderpass);
  this->create_subpass(&renderpass->subpass_0);
  this->create_renderpass_obj(renderpass);
  vk_frame->create_frame_renderpass(renderpass);
  vk_command->allocate_command_buffer(renderpass);

  //---------------------------
}
void VK_renderpass::create_color_attachment(Struct_renderpass* renderpass){
  //---------------------------

  //Attachement description
  VkAttachmentDescription color_description{};
  color_description.format = vk_color->find_color_format();
  color_description.samples = VK_SAMPLE_COUNT_1_BIT;
  color_description.loadOp = renderpass->subpass_0.color.usage;
  color_description.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
  color_description.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
  color_description.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
  color_description.initialLayout = renderpass->subpass_0.color.layout_initial;
  color_description.finalLayout = renderpass->subpass_0.color.layout_final;

  //Attachment references
  VkAttachmentReference color_reference{};
  color_reference.attachment = renderpass->subpass_0.color.binding;
  color_reference.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

  renderpass->subpass_0.color.reference = color_reference;
  renderpass->subpass_0.vec_attachment_description.push_back(color_description);

  //---------------------------
}
void VK_renderpass::create_depth_attachment(Struct_renderpass* renderpass){
  VK_depth* vk_depth = vk_engine->get_vk_depth();
  //---------------------------

  VkAttachmentDescription depth_attachment{};
  depth_attachment.format = vk_depth->find_depth_format();
  depth_attachment.samples = VK_SAMPLE_COUNT_1_BIT;
  depth_attachment.loadOp = renderpass->subpass_0.depth.usage;
  depth_attachment.storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
  depth_attachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
  depth_attachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
  depth_attachment.initialLayout = renderpass->subpass_0.depth.layout_initial;
  depth_attachment.finalLayout = renderpass->subpass_0.depth.layout_final;

  VkAttachmentReference depth_attachment_ref{};
  depth_attachment_ref.attachment = renderpass->subpass_0.depth.binding;
  depth_attachment_ref.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

  renderpass->subpass_0.depth.reference = depth_attachment_ref;
  renderpass->subpass_0.vec_attachment_description.push_back(depth_attachment);

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
  renderpass_info.attachmentCount = static_cast<uint32_t>(renderpass->subpass_0.vec_attachment_description.size());
  renderpass_info.pAttachments = renderpass->subpass_0.vec_attachment_description.data();
  renderpass_info.subpassCount = 1;
  renderpass_info.pSubpasses = &renderpass->subpass_0.description;
  renderpass_info.dependencyCount = 1;
  renderpass_info.pDependencies = &renderpass->subpass_0.dependency;

  //Render pass creation
  VkResult result = vkCreateRenderPass(vk_param->device.device, &renderpass_info, nullptr, &renderpass->renderpass);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to create render pass!");
  }

  //---------------------------
}
