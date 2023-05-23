#include "VK_pipeline.h"
#include "VK_renderpass.h"

#include "../Engine.h"
#include "../Param_vulkan.h"
#include "../Data/VK_descriptor.h"
#include "../Data/VK_data.h"
#include "../Device/VK_device.h"
#include "../Swapchain/VK_swapchain.h"
#include "../Camera/VK_viewport.h"
#include "../Shader/VK_shader.h"

//Big object that comprise:
//- data description
//- viewport info
//- dynamic state
//- shader info
//- associated render pass


//Constructor / Destructor
VK_pipeline::VK_pipeline(Engine* engineManager){
  //---------------------------

  this->engineManager = engineManager;
  this->param_vulkan = engineManager->get_param_vulkan();
  this->vk_device = engineManager->get_vk_device();
  this->vk_swapchain = engineManager->get_vk_swapchain();
  this->vk_renderpass = engineManager->get_vk_renderpass();
  this->vk_descriptor = engineManager->get_vk_descriptor();
  this->vk_viewport = engineManager->get_vk_viewport();
  this->vk_shader = engineManager->get_vk_shader();

  //---------------------------
}
VK_pipeline::~VK_pipeline(){}

//Main function
void VK_pipeline::init_pipeline(){
  //160ms/pipeline
  //---------------------------

  //Pipeline Cloud
  Struct_pipeline* pipeline_cloud = new Struct_pipeline();
  pipeline_cloud->name = "cloud";
  pipeline_cloud->topology = "point";
  pipeline_cloud->compile_shader = true;
  pipeline_cloud->path_shader_vs = "Base/shader_scene_vs";
  pipeline_cloud->path_shader_fs = "Base/shader_scene_fs";
  this->create_pipeline_info(pipeline_cloud);

  //Pipeline Glyph
  Struct_pipeline* pipeline_glyph = new Struct_pipeline();
  pipeline_glyph->name = "glyph";
  pipeline_glyph->topology = "line";
  pipeline_glyph->compile_shader = false;
  pipeline_glyph->path_shader_vs = "Base/shader_scene_vs";
  pipeline_glyph->path_shader_fs = "Base/shader_scene_fs";
  this->create_pipeline_info(pipeline_glyph);

  //Pipeline Canvas
  Struct_pipeline* pipeline_canvas = new Struct_pipeline();
  pipeline_canvas->name = "canvas";
  pipeline_canvas->topology = "triangle";
  pipeline_canvas->compile_shader = false;
  pipeline_canvas->path_shader_vs = "Base/shader_scene_vs";
  pipeline_canvas->path_shader_fs = "Base/shader_scene_fs";
  this->create_pipeline_info(pipeline_canvas);

  this->create_pipeline_graphics();

  //---------------------------
}
void VK_pipeline::cleanup(){
  //---------------------------

  for(int i=0; i<vec_pipeline.size(); i++){
    Struct_pipeline* pipeline = vec_pipeline[i];
    vkDestroyPipeline(param_vulkan->device, pipeline->pipeline, nullptr);
    vkDestroyPipelineLayout(param_vulkan->device, pipeline->pipeline_layout, nullptr);
  }

  //---------------------------
}

//Pipeline creation
void VK_pipeline::create_pipeline_info(Struct_pipeline* pipeline){
  VK_data* vk_data = engineManager->get_vk_data();
  VkRenderPass render_pass = vk_renderpass->get_renderPass();
  //---------------------------

  //Shader
  vk_shader->compute_shader_module(pipeline);
  VkShaderModule module_vert = vk_shader->get_module_vert();
  VkShaderModule module_frag = vk_shader->get_module_frag();
  pipeline->vec_shader_module.push_back(module_vert);
  pipeline->vec_shader_module.push_back(module_frag);

  //Pipeline element info
  pipeline->dynamic_state_object.push_back(VK_DYNAMIC_STATE_VIEWPORT);
  pipeline->dynamic_state_object.push_back(VK_DYNAMIC_STATE_SCISSOR);
  pipeline->dynamic_state_object.push_back(VK_DYNAMIC_STATE_LINE_WIDTH);
  pipeline->shader_stage = vk_shader->pipeline_shader_info(module_vert, module_frag);
  pipeline->data_description = vk_data->description_binding();
  pipeline->attribut_description = vk_data->description_vertex();
  pipeline->vertex_input_info = pipe_data_description(pipeline->data_description, pipeline->attribut_description);
  pipeline->input_assembly = pipe_topology(pipeline->topology);
  pipeline->dynamic_state = pipe_dynamic_state(pipeline->dynamic_state_object);
  pipeline->viewport_state = pipe_viewport();
  pipeline->rasterizer = pipe_raster();
  pipeline->multisampling = pipe_multisampling();
  pipeline->color_blend_attachment = pipe_color_blending_state();
  pipeline->color_blend_info = pipe_color_blending(&pipeline->color_blend_attachment);
  pipeline->depth_stencil = pipe_depth();
  this->create_pipeline_layout(pipeline);


  //Pipeline info
  VkGraphicsPipelineCreateInfo pipeline_info{};
  pipeline_info.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
  pipeline_info.stageCount = 2;
  pipeline_info.pStages = pipeline->shader_stage.data();
  pipeline_info.pVertexInputState = &pipeline->vertex_input_info;
  pipeline_info.pInputAssemblyState = &pipeline->input_assembly;
  pipeline_info.pViewportState = &pipeline->viewport_state;
  pipeline_info.pRasterizationState = &pipeline->rasterizer;
  pipeline_info.pMultisampleState = &pipeline->multisampling;
  pipeline_info.pDepthStencilState = &pipeline->depth_stencil;
  pipeline_info.pColorBlendState = &pipeline->color_blend_info;
  pipeline_info.pDynamicState = &pipeline->dynamic_state;
  pipeline_info.layout = pipeline->pipeline_layout;
  pipeline_info.renderPass = render_pass;
  pipeline_info.subpass = 0;
  pipeline_info.basePipelineHandle = VK_NULL_HANDLE; // Optional
  pipeline_info.basePipelineIndex = -1; // Optional

  pipeline->pipeline_info = pipeline_info;
  this->vec_pipeline.push_back(pipeline);

  //---------------------------
}
void VK_pipeline::create_pipeline_layout(Struct_pipeline* pipeline){
  //---------------------------

  //Push constant for MVP matrix
  VkPushConstantRange pushconstant_range = {};
  pushconstant_range.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
  pushconstant_range.offset = 0;
  pushconstant_range.size = sizeof(glm::mat4);

  //Pipeline layout info -> usefull for shader uniform variables
  VkDescriptorSetLayout descriptor_layout = vk_descriptor->get_descriptor_layout();
  VkPipelineLayoutCreateInfo pipeline_layout_info{};
  pipeline_layout_info.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
  pipeline_layout_info.setLayoutCount = 1;
  pipeline_layout_info.pSetLayouts = &descriptor_layout;
  pipeline_layout_info.pushConstantRangeCount = 1;
  pipeline_layout_info.pPushConstantRanges = &pushconstant_range;

  //Pipeline layout creation
  VkResult result = vkCreatePipelineLayout(param_vulkan->device, &pipeline_layout_info, nullptr, &pipeline->pipeline_layout);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to create pipeline layout!");
  }

  //---------------------------
}
void VK_pipeline::create_pipeline_graphics(){
  //---------------------------

  vector<VkGraphicsPipelineCreateInfo> vec_pipeline_info;
  for(int i=0; i<vec_pipeline.size(); i++){
    Struct_pipeline* pipeline = vec_pipeline[i];
    vec_pipeline_info.push_back(pipeline->pipeline_info);
  }

  vector<VkPipeline> vec_pipeline_obj(vec_pipeline.size());
  VkResult result = vkCreateGraphicsPipelines(param_vulkan->device, VK_NULL_HANDLE, vec_pipeline_info.size(), vec_pipeline_info.data(), nullptr, vec_pipeline_obj.data());
  if(result != VK_SUCCESS){
      throw std::runtime_error("[error] failed to create graphics pipeline!");
    }

  for(int i=0; i<vec_pipeline.size(); i++){
    Struct_pipeline* pipeline = vec_pipeline[i];
    pipeline->pipeline = vec_pipeline_obj[i];

    //Destroy shader modules
    for(int i=0; i<pipeline->vec_shader_module.size(); i++){
      vkDestroyShaderModule(param_vulkan->device, pipeline->vec_shader_module[i], nullptr);
    }
  }

  //---------------------------
}

//Pipeline element
VkPipelineVertexInputStateCreateInfo VK_pipeline::pipe_data_description(vector<VkVertexInputBindingDescription>& data_description, vector<VkVertexInputAttributeDescription>& attribut_description){
  //---------------------------

  VkPipelineVertexInputStateCreateInfo vertex_input_info{};
  vertex_input_info.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
  vertex_input_info.vertexBindingDescriptionCount = static_cast<uint32_t>(data_description.size());
  vertex_input_info.vertexAttributeDescriptionCount = static_cast<uint32_t>(attribut_description.size());
  vertex_input_info.pVertexBindingDescriptions = data_description.data();
  vertex_input_info.pVertexAttributeDescriptions = attribut_description.data();

  //---------------------------
  return vertex_input_info;
}
VkPipelineDynamicStateCreateInfo VK_pipeline::pipe_dynamic_state(std::vector<VkDynamicState>& dynamic_state_obj){
  //---------------------------

  //Dynamic internal variables (viewport, line width, ...)
  //the subsequent values has to be given at runtime
  VkPipelineDynamicStateCreateInfo dynamic_state{};
  dynamic_state.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
  dynamic_state.dynamicStateCount = static_cast<uint32_t>(dynamic_state_obj.size());
  dynamic_state.pDynamicStates = dynamic_state_obj.data();

  //---------------------------
  return dynamic_state;
}
VkPipelineViewportStateCreateInfo VK_pipeline::pipe_viewport(){
  //---------------------------

  //Viewport
  vk_viewport->update_viewport(param_vulkan->extent);
  VkViewport viewport = vk_viewport->get_viewport();
  VkRect2D scissor = vk_viewport->get_scissor();

  //Viewport info
  VkPipelineViewportStateCreateInfo viewport_state{};
  viewport_state.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
  viewport_state.viewportCount = 1;
  viewport_state.pViewports = &viewport;
  viewport_state.scissorCount = 1;
  viewport_state.pScissors = &scissor;

  //---------------------------
  return viewport_state;
}
VkPipelineRasterizationStateCreateInfo VK_pipeline::pipe_raster(){
  //---------------------------

  VkPipelineRasterizationStateCreateInfo rasterizer{};
  rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
  rasterizer.depthClampEnable = VK_FALSE;
  rasterizer.rasterizerDiscardEnable = VK_FALSE;
  rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
  rasterizer.lineWidth = 1.0f;
  rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
  rasterizer.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
  rasterizer.depthBiasEnable = VK_FALSE;
  rasterizer.depthBiasConstantFactor = 0.0f; // Optional
  rasterizer.depthBiasClamp = 0.0f; // Optional
  rasterizer.depthBiasSlopeFactor = 0.0f; // Optional

  //---------------------------
  return rasterizer;
}
VkPipelineMultisampleStateCreateInfo VK_pipeline::pipe_multisampling(){
  //---------------------------

  VkPipelineMultisampleStateCreateInfo multisampling{};
  multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
  multisampling.sampleShadingEnable = VK_FALSE;
  multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
  multisampling.minSampleShading = 1.0f; // Optional
  multisampling.pSampleMask = nullptr; // Optional
  multisampling.alphaToCoverageEnable = VK_FALSE; // Optional
  multisampling.alphaToOneEnable = VK_FALSE; // Optional

  //---------------------------
  return multisampling;
}
VkPipelineDepthStencilStateCreateInfo VK_pipeline::pipe_depth(){
  //---------------------------

  VkPipelineDepthStencilStateCreateInfo depth_stencil = {};
  depth_stencil.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
  depth_stencil.depthTestEnable = VK_TRUE;
  depth_stencil.depthWriteEnable = VK_TRUE;
  depth_stencil.depthCompareOp = VK_COMPARE_OP_LESS;
  depth_stencil.depthBoundsTestEnable = VK_FALSE;
  depth_stencil.minDepthBounds = 0.0f; // Optional
  depth_stencil.maxDepthBounds = 1.0f; // Optional
  depth_stencil.stencilTestEnable = VK_FALSE;
  depth_stencil.front = {}; // Optional
  depth_stencil.back = {}; // Optional

  //---------------------------
  return depth_stencil;
}
VkPipelineColorBlendAttachmentState VK_pipeline::pipe_color_blending_state(){
  //---------------------------

  VkPipelineColorBlendAttachmentState color_blend_attachment{};
  color_blend_attachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
  color_blend_attachment.blendEnable = VK_FALSE;
  color_blend_attachment.srcColorBlendFactor = VK_BLEND_FACTOR_ONE; // Optional
  color_blend_attachment.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO; // Optional
  color_blend_attachment.colorBlendOp = VK_BLEND_OP_ADD; // Optional
  color_blend_attachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE; // Optional
  color_blend_attachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO; // Optional
  color_blend_attachment.alphaBlendOp = VK_BLEND_OP_ADD; // Optional

  //---------------------------
  return color_blend_attachment;
}
VkPipelineColorBlendStateCreateInfo VK_pipeline::pipe_color_blending(VkPipelineColorBlendAttachmentState* color_blend_attachment){
  //---------------------------

  VkPipelineColorBlendStateCreateInfo color_blend_info{};
  color_blend_info.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
  color_blend_info.logicOpEnable = VK_FALSE;
  color_blend_info.logicOp = VK_LOGIC_OP_COPY; // Optional
  color_blend_info.attachmentCount = 1;
  color_blend_info.pAttachments = color_blend_attachment;
  color_blend_info.blendConstants[0] = 0.0f; // Optional
  color_blend_info.blendConstants[1] = 0.0f; // Optional
  color_blend_info.blendConstants[2] = 0.0f; // Optional
  color_blend_info.blendConstants[3] = 0.0f; // Optional

  //---------------------------
  return color_blend_info;
}
VkPipelineInputAssemblyStateCreateInfo VK_pipeline::pipe_topology(string topology){
  //---------------------------

  VkPipelineInputAssemblyStateCreateInfo input_assembly{};
  input_assembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
  input_assembly.primitiveRestartEnable = VK_FALSE;

  if(topology == "point"){
    input_assembly.topology = VK_PRIMITIVE_TOPOLOGY_POINT_LIST;
  }
  else if(topology == "line"){
    input_assembly.topology = VK_PRIMITIVE_TOPOLOGY_LINE_LIST;
  }
  else if(topology == "triangle"){
    input_assembly.topology = VK_PRIMITIVE_TOPOLOGY_LINE_LIST;
  }

  //---------------------------
  return input_assembly;
}

//Subfunction
Struct_pipeline* VK_pipeline::get_pipeline_byName(string name){
  //---------------------------

  for(int i=0; i<vec_pipeline.size(); i++){
    Struct_pipeline* pipeline = vec_pipeline[i];
    if(name == pipeline->name){
      return pipeline;
    }
  }

  //---------------------------
  cout<<"[error] pipeline name problem"<<endl;
  return nullptr;
}
