#include "VK_renderpass.h"

#include "../VK_pipeline.h"
#include "../Attachment/VK_depth.h"
#include "../Attachment/VK_color.h"

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

  //---------------------------
}
VK_renderpass::~VK_renderpass(){}

//Main function
void VK_renderpass::init_renderpass(){
  VK_depth* vk_depth = vk_engine->get_vk_depth();
  //---------------------------

  this->init_renderpass_scene();
  this->init_renderpass_glyph();
  this->init_renderpass_canvas();
  this->init_renderpass_gui();

  //---------------------------
}
void VK_renderpass::clean_renderpass(){
  VK_frame* vk_frame = vk_engine->get_vk_frame();
  //---------------------------

  //vk_frame->clean_frame_renderpass(&vk_param->renderpass_canvas);
  //vk_frame->clean_frame_renderpass(&vk_param->renderpass_glyph);
  //vk_frame->clean_frame_renderpass(&vk_param->renderpass_canvas);
  //vk_frame->clean_frame_renderpass(&vk_param->renderpass_gui);

  vk_frame->clean_frame_renderpass(&vk_param->renderpass_scene);
  vk_frame->clean_frame_renderpass(&vk_param->renderpass_canvas);
  vkDestroyRenderPass(vk_param->device.device, vk_param->renderpass_scene.renderpass, nullptr);
  vkDestroyRenderPass(vk_param->device.device, vk_param->renderpass_glyph.renderpass, nullptr);
  vkDestroyRenderPass(vk_param->device.device, vk_param->renderpass_canvas.renderpass, nullptr);
  vkDestroyRenderPass(vk_param->device.device, vk_param->renderpass_gui.renderpass, nullptr);

  VK_pipeline* vk_pipeline = vk_engine->get_vk_pipeline();
  vk_pipeline->clean_pipeline(&vk_param->renderpass_scene.pipeline);
  vk_pipeline->clean_pipeline(&vk_param->renderpass_glyph.pipeline);
  vk_pipeline->clean_pipeline(&vk_param->renderpass_canvas.pipeline);
  vk_pipeline->clean_pipeline(&vk_param->renderpass_gui.pipeline);

  //---------------------------
}

//Render pass objects
void VK_renderpass::init_renderpass_scene(){
  VK_depth* vk_depth = vk_engine->get_vk_depth();
  VK_pipeline* vk_pipeline = vk_engine->get_vk_pipeline();
  //---------------------------

  //Render pass scene
  Struct_renderpass* renderpass = &vk_param->renderpass_scene;
  renderpass->name = "scene";
  renderpass->attachment.usage = ATTACHMENT_USAGE_CLEAR;
  renderpass->attachment.color_layout_initial = IMAGE_LAYOUT_EMPTY;
  renderpass->attachment.color_layout_final = IMAGE_LAYOUT_PRESENT;
  renderpass->attachment.depth_layout_initial = IMAGE_LAYOUT_EMPTY;
  renderpass->attachment.depth_layout_final = IMAGE_LAYOUT_DEPTH;
  this->create_renderpass(renderpass);

  Struct_pipeline* pipeline = new Struct_pipeline();
  pipeline->name = "scene";
  pipeline->topology = "point";
  pipeline->compile_shader = true;
  pipeline->path_shader_vs = "Base/shader_scene_vs";
  pipeline->path_shader_fs = "Base/shader_scene_fs";
  pipeline->vec_data_name.push_back("location");
  pipeline->vec_data_name.push_back("color");
  pipeline->renderpass = renderpass;
  pipeline->binding.vec_required_binding.push_back(std::make_tuple("mvp", "mat4", 0, TYPE_UNIFORM, STAGE_VS));
  vk_pipeline->create_pipeline(pipeline);

  renderpass->pipeline = pipeline;

  //---------------------------
}
void VK_renderpass::init_renderpass_glyph(){
  VK_depth* vk_depth = vk_engine->get_vk_depth();
  VK_pipeline* vk_pipeline = vk_engine->get_vk_pipeline();
  //---------------------------

  Struct_renderpass* renderpass = &vk_param->renderpass_glyph;
  renderpass->name = "glyph";
  renderpass->attachment.usage = ATTACHMENT_USAGE_CLEAR;
  renderpass->attachment.color_layout_initial = IMAGE_LAYOUT_EMPTY;
  renderpass->attachment.color_layout_final = IMAGE_LAYOUT_PRESENT;
  renderpass->attachment.depth_layout_initial = IMAGE_LAYOUT_EMPTY;
  renderpass->attachment.depth_layout_final = IMAGE_LAYOUT_DEPTH;
  this->create_renderpass(renderpass);

  Struct_pipeline* pipeline = new Struct_pipeline();
  pipeline->name = "glyph";
  pipeline->topology = "line";
  pipeline->compile_shader = true;
  pipeline->path_shader_vs = "Base/shader_glyph_vs";
  pipeline->path_shader_fs = "Base/shader_glyph_fs";
  pipeline->vec_data_name.push_back("location");
  pipeline->vec_data_name.push_back("color");
  pipeline->renderpass = renderpass;
  pipeline->binding.vec_required_binding.push_back(std::make_tuple("mvp", "mat4", 0, TYPE_UNIFORM, STAGE_VS));
  vk_pipeline->create_pipeline(pipeline);

  renderpass->pipeline = pipeline;

  //---------------------------
}
void VK_renderpass::init_renderpass_canvas(){
  VK_depth* vk_depth = vk_engine->get_vk_depth();
  VK_pipeline* vk_pipeline = vk_engine->get_vk_pipeline();
  //---------------------------

  Struct_renderpass* renderpass = &vk_param->renderpass_canvas;
  renderpass->name = "canvas";
  renderpass->attachment.usage = ATTACHMENT_USAGE_CLEAR;
  renderpass->attachment.color_layout_initial = IMAGE_LAYOUT_EMPTY;
  renderpass->attachment.color_layout_final = IMAGE_LAYOUT_PRESENT;
  renderpass->attachment.depth_layout_initial = IMAGE_LAYOUT_EMPTY;
  renderpass->attachment.depth_layout_final = IMAGE_LAYOUT_DEPTH;
  this->create_renderpass(renderpass);

  Struct_pipeline* pipeline = new Struct_pipeline();
  pipeline->name = "canvas";
  pipeline->topology = "triangle";
  pipeline->compile_shader = true;
  pipeline->path_shader_vs = "Base/shader_canvas_vs";
  pipeline->path_shader_fs = "Base/shader_canvas_fs";
  pipeline->vec_data_name.push_back("location");
  pipeline->vec_data_name.push_back("tex_coord");
  pipeline->renderpass = renderpass;
  pipeline->binding.vec_required_binding.push_back(std::make_tuple("mvp", "mat4", 0, TYPE_UNIFORM, STAGE_VS));
  pipeline->binding.vec_required_binding.push_back(std::make_tuple("texture", "", 1, TYPE_SAMPLER, STAGE_FS));
  vk_pipeline->create_pipeline(pipeline);

  renderpass->pipeline = pipeline;

  //---------------------------
}
void VK_renderpass::init_renderpass_gui(){
  VK_depth* vk_depth = vk_engine->get_vk_depth();
  VK_pipeline* vk_pipeline = vk_engine->get_vk_pipeline();
  //---------------------------

  Struct_renderpass* renderpass = &vk_param->renderpass_gui;
  renderpass->name = "gui";
  renderpass->attachment.usage = ATTACHMENT_USAGE_CONSERVE;
  renderpass->attachment.color_layout_initial = IMAGE_LAYOUT_PRESENT;
  renderpass->attachment.color_layout_final = IMAGE_LAYOUT_PRESENT;
  renderpass->attachment.depth_layout_initial = IMAGE_LAYOUT_DEPTH;
  renderpass->attachment.depth_layout_final = IMAGE_LAYOUT_DEPTH;
  this->create_renderpass(renderpass);

  Struct_pipeline* pipeline = new Struct_pipeline();
  pipeline->name = "scene";
  pipeline->topology = "point";
  pipeline->compile_shader = true;
  pipeline->path_shader_vs = "Base/shader_scene_vs";
  pipeline->path_shader_fs = "Base/shader_scene_fs";
  pipeline->vec_data_name.push_back("location");
  pipeline->vec_data_name.push_back("color");
  pipeline->renderpass = renderpass;
  pipeline->binding.vec_required_binding.push_back(std::make_tuple("mvp", "mat4", 0, TYPE_UNIFORM, STAGE_VS));
  vk_pipeline->create_pipeline(pipeline);

  renderpass->pipeline = pipeline;

  //---------------------------
}

//Subfunction
void VK_renderpass::create_renderpass(Struct_renderpass* renderpass){
  VK_depth* vk_depth = vk_engine->get_vk_depth();
  VK_frame* vk_frame = vk_engine->get_vk_frame();
  //---------------------------

  this->create_color_attachment(renderpass);
  this->create_depth_attachment(renderpass);
  this->create_subpass(renderpass);
  this->create_renderpass_info(renderpass);
  this->create_renderpass_obj(renderpass);
  //vk_frame->create_frame_renderpass(renderpass);

  //---------------------------
}
void VK_renderpass::create_depth_attachment(Struct_renderpass* renderpass){
  VK_depth* vk_depth = vk_engine->get_vk_depth();
  //---------------------------

  VkAttachmentDescription depth_attachment{};
  depth_attachment.format = vk_depth->find_depth_format();
  depth_attachment.samples = VK_SAMPLE_COUNT_1_BIT;
  depth_attachment.loadOp = renderpass->attachment.usage;
  depth_attachment.storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
  depth_attachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
  depth_attachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
  depth_attachment.initialLayout = renderpass->attachment.depth_layout_initial;
  depth_attachment.finalLayout = renderpass->attachment.depth_layout_final;

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
  color_description.loadOp = renderpass->attachment.usage;
  color_description.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
  color_description.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
  color_description.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
  color_description.initialLayout = renderpass->attachment.color_layout_initial;
  color_description.finalLayout = renderpass->attachment.color_layout_final;

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
