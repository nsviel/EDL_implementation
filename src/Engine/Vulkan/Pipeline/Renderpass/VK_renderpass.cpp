#include "VK_renderpass.h"
#include "VK_subpass.h"

#include "../Command/VK_command.h"
#include "../Pipeline/VK_pipeline.h"
#include "../Image/VK_color.h"
#include "../Image/VK_depth.h"

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
  this->vk_subpass = new VK_subpass(vk_engine);

  //---------------------------
}
VK_renderpass::~VK_renderpass(){}

//Main function
void VK_renderpass::init_renderpass(){
  //---------------------------

  this->init_renderpass_scene();
  this->init_renderpass_canvas();
  this->init_renderpass_gui();

  //---------------------------
}
void VK_renderpass::clean_renderpass(){
  //---------------------------

  this->clean_renderpass_object(&vk_param->renderpass_scene);
  this->clean_renderpass_object(&vk_param->renderpass_canvas);
  this->clean_renderpass_object(&vk_param->renderpass_gui);

  //---------------------------
}
void VK_renderpass::clean_renderpass_object(Struct_renderpass* renderpass){
  VK_frame* vk_frame = vk_engine->get_vk_frame();
  //---------------------------

  vk_frame->clean_frame_renderpass(renderpass);
  vkDestroyRenderPass(vk_param->device.device, renderpass->renderpass, nullptr);
  vk_pipeline->clean_pipeline(renderpass);

  //---------------------------
}

//Render pass objects
void VK_renderpass::init_renderpass_scene(){
  //---------------------------

  //Render pass
  Struct_renderpass* renderpass = &vk_param->renderpass_scene;
  renderpass->name = "scene";
  //renderpass->frame_usage = IMAGE_USAGE_ATTACHMENT | IMAGE_USAGE_SAMPLER;
  renderpass->frame_usage = IMAGE_USAGE_DEPTH;

  //Subpass
  Struct_subpass* subpass = new Struct_subpass();

  subpass->color.binding = 0;
  subpass->color.usage = ATTACHMENT_USAGE_CLEAR;
  subpass->color.layout_initial = IMAGE_LAYOUT_EMPTY;
  subpass->color.layout_final = IMAGE_LAYOUT_SHADER;

  subpass->depth.binding = 1;
  subpass->depth.usage = ATTACHMENT_USAGE_CLEAR;
  subpass->depth.layout_initial = IMAGE_LAYOUT_EMPTY;
  subpass->depth.layout_final = IMAGE_LAYOUT_DEPTH;



  subpass->color.binding = 0;
  subpass->color.usage = ATTACHMENT_USAGE_CLEAR;
  subpass->color.layout_initial = IMAGE_LAYOUT_EMPTY;
  subpass->color.layout_final = IMAGE_LAYOUT_COLOR;

  subpass->depth.binding = 1;
  subpass->depth.usage = ATTACHMENT_USAGE_CLEAR;
  subpass->depth.layout_initial = IMAGE_LAYOUT_EMPTY;
  subpass->depth.layout_final = IMAGE_LAYOUT_DEPTH;

  renderpass->vec_subpass.push_back(subpass);

  //Pipeline
  Struct_pipeline* pipeline_point = new Struct_pipeline();
  pipeline_point->name = "topology_point";
  pipeline_point->topology = "point";
  pipeline_point->compile_shader = true;
  pipeline_point->path_shader_vs = "Base/shader_scene_vs";
  pipeline_point->path_shader_fs = "Base/shader_scene_fs";
  pipeline_point->vec_data_name.push_back("location");
  pipeline_point->vec_data_name.push_back("color");
  pipeline_point->binding.vec_required_binding.push_back(std::make_tuple("mvp", "mat4", 0, TYPE_UNIFORM, STAGE_VS));
  renderpass->vec_pipeline.push_back(pipeline_point);

  Struct_pipeline* pipeline_line = new Struct_pipeline();
  pipeline_line->name = "topology_line";
  pipeline_line->topology = "line";
  pipeline_line->compile_shader = true;
  pipeline_line->path_shader_vs = "Base/shader_scene_vs";
  pipeline_line->path_shader_fs = "Base/shader_scene_fs";
  pipeline_line->vec_data_name.push_back("location");
  pipeline_line->vec_data_name.push_back("color");
  pipeline_line->binding.vec_required_binding.push_back(std::make_tuple("mvp", "mat4", 0, TYPE_UNIFORM, STAGE_VS));
  renderpass->vec_pipeline.push_back(pipeline_line);

  //---------------------------
  this->create_renderpass(renderpass);
  this->create_renderpass_frame(renderpass, "sw");
}
void VK_renderpass::init_renderpass_canvas(){
  //---------------------------

  //Render pass
  Struct_renderpass* renderpass = &vk_param->renderpass_canvas;
  renderpass->name = "canvas";
  renderpass->frame_set = vk_param->renderpass_scene.frame_set;
  renderpass->frame_usage = IMAGE_USAGE_DEPTH;

  //Subpass
  Struct_subpass* subpass = new Struct_subpass();

  subpass->color.binding = 0;
  subpass->color.usage = ATTACHMENT_USAGE_CLEAR;
  subpass->color.layout_initial = IMAGE_LAYOUT_EMPTY;
  subpass->color.layout_final = IMAGE_LAYOUT_COLOR;

  subpass->depth.binding = 1;
  subpass->depth.usage = ATTACHMENT_USAGE_CLEAR;
  subpass->depth.layout_initial = IMAGE_LAYOUT_EMPTY;
  subpass->depth.layout_final = IMAGE_LAYOUT_DEPTH;



  subpass->color.binding = 0;
  subpass->color.usage = ATTACHMENT_USAGE_CONSERVE;
  subpass->color.layout_initial = IMAGE_LAYOUT_COLOR;
  subpass->color.layout_final = IMAGE_LAYOUT_COLOR;

  subpass->depth.binding = 1;
  subpass->depth.usage = ATTACHMENT_USAGE_CLEAR;
  subpass->depth.layout_initial = IMAGE_LAYOUT_EMPTY;
  subpass->depth.layout_final = IMAGE_LAYOUT_DEPTH;

  renderpass->vec_subpass.push_back(subpass);

  //Pipeline
  Struct_pipeline* pipeline = new Struct_pipeline();
  pipeline->name = "topology_triangle";
  pipeline->topology = "triangle";
  pipeline->compile_shader = true;
  pipeline->path_shader_vs = "Base/shader_canvas_vs";
  pipeline->path_shader_fs = "Base/shader_canvas_fs";
  pipeline->vec_data_name.push_back("location");
  pipeline->vec_data_name.push_back("tex_coord");
  pipeline->binding.vec_required_binding.push_back(std::make_tuple("mvp", "mat4", 0, TYPE_UNIFORM, STAGE_VS));
  pipeline->binding.vec_required_binding.push_back(std::make_tuple("texture", "", 1, TYPE_SAMPLER, STAGE_FS));
  renderpass->vec_pipeline.push_back(pipeline);

  //---------------------------
  this->create_renderpass(renderpass);
  this->create_renderpass_frame(renderpass, "sw");
}
void VK_renderpass::init_renderpass_gui(){
  //---------------------------

  //Render pass
  Struct_renderpass* renderpass = &vk_param->renderpass_gui;
  renderpass->name = "canvas";
  renderpass->frame_set = vk_param->renderpass_canvas.frame_set;
  renderpass->frame_usage = IMAGE_USAGE_DEPTH;

  //Subpass
  Struct_subpass* subpass = new Struct_subpass();
  subpass->color.binding = 0;
  subpass->color.usage = ATTACHMENT_USAGE_CONSERVE;
  subpass->color.layout_initial = IMAGE_LAYOUT_COLOR;
  subpass->color.layout_final = IMAGE_LAYOUT_PRESENT;

  subpass->depth.binding = 1;
  subpass->depth.usage = ATTACHMENT_USAGE_CLEAR;
  subpass->depth.layout_initial = IMAGE_LAYOUT_EMPTY;
  subpass->depth.layout_final = IMAGE_LAYOUT_DEPTH;
  renderpass->vec_subpass.push_back(subpass);

  //Pipeline
  Struct_pipeline* pipeline = new Struct_pipeline();
  pipeline->name = "topology_triangle";
  pipeline->topology = "triangle";
  pipeline->compile_shader = true;
  pipeline->path_shader_vs = "Base/shader_canvas_vs";
  pipeline->path_shader_fs = "Base/shader_canvas_fs";
  pipeline->vec_data_name.push_back("location");
  pipeline->vec_data_name.push_back("tex_coord");
  pipeline->binding.vec_required_binding.push_back(std::make_tuple("mvp", "mat4", 0, TYPE_UNIFORM, STAGE_VS));
  pipeline->binding.vec_required_binding.push_back(std::make_tuple("texture", "", 1, TYPE_SAMPLER, STAGE_FS));
  renderpass->vec_pipeline.push_back(pipeline);

  //---------------------------
  this->create_renderpass(renderpass);
  this->create_renderpass_frame(renderpass, "sw");
}

//Subfunction
void VK_renderpass::create_renderpass(Struct_renderpass* renderpass){
  VK_command* vk_command = vk_engine->get_vk_command();
  //---------------------------

  this->create_color_attachment(renderpass);
  this->create_depth_attachment(renderpass);
  this->create_subpass(renderpass->vec_subpass[0]);
  this->create_renderpass_obj(renderpass);
  vk_command->allocate_command_buffer(renderpass);
  vk_pipeline->create_pipeline(renderpass);

  //---------------------------
}
void VK_renderpass::create_color_attachment(Struct_renderpass* renderpass){
  //---------------------------

  //Attachement description
  VkAttachmentDescription color_description{};
  color_description.format = vk_color->find_color_format();
  color_description.samples = VK_SAMPLE_COUNT_1_BIT;
  color_description.loadOp = renderpass->vec_subpass[0]->color.usage;
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
  depth_attachment.loadOp = renderpass->vec_subpass[0]->depth.usage;
  depth_attachment.storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
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
void VK_renderpass::create_renderpass_frame(Struct_renderpass* renderpass, string sw_or_rp){
  VK_frame* vk_frame = vk_engine->get_vk_frame();
  //---------------------------

  if(renderpass->frame_set != nullptr) return;

  if(sw_or_rp == "sw"){
    renderpass->frame_set = new Frame_set();
    vk_frame->create_frame_swapchain(renderpass);
  }else if(sw_or_rp == "rp"){
    renderpass->frame_set = new Frame_set();
    vk_frame->create_frame_renderpass(renderpass);
  }

  //---------------------------
}
