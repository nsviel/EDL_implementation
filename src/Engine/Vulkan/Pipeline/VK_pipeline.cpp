#include "VK_pipeline.h"
#include "VK_renderpass.h"

#include "../Engine.h"
#include "../Param_vulkan.h"
#include "../Shader/VK_descriptor.h"
#include "../Data/VK_data.h"
#include "../Device/VK_device.h"
#include "../Swapchain/VK_swapchain.h"
#include "../Camera/VK_viewport.h"
#include "../Shader/VK_shader.h"
#include "../Shader/VK_uniform.h"


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
  this->vk_data = engineManager->get_vk_data();
  this->vk_uniform = engineManager->get_vk_uniform();

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
  pipeline_cloud->vec_data_name.push_back("location");
  pipeline_cloud->vec_data_name.push_back("color");
  pipeline_cloud->descriptor_layout = vk_descriptor->create_layout_basic();
  this->create_pipeline_info(pipeline_cloud);

  //Pipeline Glyph
  Struct_pipeline* pipeline_glyph = new Struct_pipeline();
  pipeline_glyph->name = "glyph";
  pipeline_glyph->topology = "line";
  pipeline_glyph->compile_shader = true;
  pipeline_glyph->path_shader_vs = "Base/shader_glyph_vs";
  pipeline_glyph->path_shader_fs = "Base/shader_glyph_fs";
  pipeline_glyph->vec_data_name.push_back("location");
  pipeline_glyph->vec_data_name.push_back("color");
  pipeline_glyph->descriptor_layout = vk_descriptor->create_layout_basic();
  this->create_pipeline_info(pipeline_glyph);

  //Pipeline Canvas
  Struct_pipeline* pipeline_canvas = new Struct_pipeline();
  pipeline_canvas->name = "canvas";
  pipeline_canvas->topology = "triangle";
  pipeline_canvas->compile_shader = true;
  pipeline_canvas->path_shader_vs = "Base/shader_canvas_vs";
  pipeline_canvas->path_shader_fs = "Base/shader_canvas_fs";
  pipeline_canvas->vec_data_name.push_back("location");
  pipeline_canvas->vec_data_name.push_back("tex_coord");
  pipeline_canvas->descriptor_layout = vk_descriptor->create_layout_canvas();
  this->create_pipeline_info(pipeline_canvas);

  this->create_pipeline_graphics();
  vk_descriptor->allocate_descriptor_set(vec_pipeline);

  //---------------------------
}
void VK_pipeline::cleanup(){
  //---------------------------

  for(int i=0; i<vec_pipeline.size(); i++){
    Struct_pipeline* pipeline = vec_pipeline[i];
    vkDestroyPipeline(param_vulkan->device, pipeline->pipeline, nullptr);
    vkDestroyPipelineLayout(param_vulkan->device, pipeline->pipeline_layout, nullptr);
    vkDestroyDescriptorSetLayout(param_vulkan->device, pipeline->descriptor_layout, nullptr);
    vk_uniform->clean_uniform(pipeline);
  }

  //---------------------------
}

//Pipeline creation
void VK_pipeline::create_pipeline_info(Struct_pipeline* pipeline){
  //---------------------------

  //Dynamic
  pipeline->dynamic_state_object.push_back(VK_DYNAMIC_STATE_VIEWPORT);
  pipeline->dynamic_state_object.push_back(VK_DYNAMIC_STATE_SCISSOR);
  pipeline->dynamic_state_object.push_back(VK_DYNAMIC_STATE_LINE_WIDTH);

  //Pipeline elements
  vk_uniform->create_uniform_buffers(pipeline);
  vk_shader->create_pipeline_shader(pipeline);
  vk_data->create_pipeline_data(pipeline);
  this->create_pipeline_layout(pipeline);
  this->create_topology(pipeline);
  this->create_dynamic_state(pipeline);
  this->create_viewport(pipeline);
  this->create_raster(pipeline);
  this->create_multisampling(pipeline);
  this->create_color_blending_state(pipeline);
  this->create_color_blending(pipeline);
  this->create_depth(pipeline);

  //Pipeline info
  VkGraphicsPipelineCreateInfo pipeline_info{};
  pipeline_info.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
  pipeline_info.stageCount = static_cast<uint32_t>(pipeline->shader_stage.size());
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
  pipeline_info.renderPass = vk_renderpass->get_renderPass();
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
  pushconstant_range.stageFlags = STAGE_VS;
  pushconstant_range.offset = 0;
  pushconstant_range.size = sizeof(glm::mat4);

  //Pipeline layout info -> usefull for shader uniform variables
  VkPipelineLayoutCreateInfo pipeline_layout_info{};
  pipeline_layout_info.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
  pipeline_layout_info.setLayoutCount = 1;
  pipeline_layout_info.pSetLayouts = &pipeline->descriptor_layout;
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
    for(int i=0; i<pipeline->vec_shader_couple.size(); i++){
      pair<VkShaderModule, VkShaderModule> shader_couple = pipeline->vec_shader_couple[i];
      vkDestroyShaderModule(param_vulkan->device, shader_couple.first, nullptr);
      vkDestroyShaderModule(param_vulkan->device, shader_couple.second, nullptr);
    }
  }

  //---------------------------
}

//Pipeline element
void VK_pipeline::create_dynamic_state(Struct_pipeline* pipeline){
  //---------------------------

  //Dynamic internal variables (viewport, line width, ...)
  //the subsequent values has to be given at runtime
  VkPipelineDynamicStateCreateInfo dynamic_state{};
  dynamic_state.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
  dynamic_state.dynamicStateCount = static_cast<uint32_t>(pipeline->dynamic_state_object.size());
  dynamic_state.pDynamicStates = pipeline->dynamic_state_object.data();

  //---------------------------
  pipeline->dynamic_state = dynamic_state;
}
void VK_pipeline::create_viewport(Struct_pipeline* pipeline){
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
  pipeline->viewport_state = viewport_state;
}
void VK_pipeline::create_raster(Struct_pipeline* pipeline){
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
  pipeline->rasterizer = rasterizer;
}
void VK_pipeline::create_multisampling(Struct_pipeline* pipeline){
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
  pipeline->multisampling = multisampling;
}
void VK_pipeline::create_depth(Struct_pipeline* pipeline){
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
  pipeline->depth_stencil = depth_stencil;
}
void VK_pipeline::create_color_blending_state(Struct_pipeline* pipeline){
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

  pipeline->color_blend_attachment = color_blend_attachment;
}
void VK_pipeline::create_color_blending(Struct_pipeline* pipeline){
  //---------------------------

  VkPipelineColorBlendStateCreateInfo color_blend_info{};
  color_blend_info.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
  color_blend_info.logicOpEnable = VK_FALSE;
  color_blend_info.logicOp = VK_LOGIC_OP_COPY; // Optional
  color_blend_info.attachmentCount = 1;
  color_blend_info.pAttachments = &pipeline->color_blend_attachment;
  color_blend_info.blendConstants[0] = 0.0f; // Optional
  color_blend_info.blendConstants[1] = 0.0f; // Optional
  color_blend_info.blendConstants[2] = 0.0f; // Optional
  color_blend_info.blendConstants[3] = 0.0f; // Optional

  //---------------------------
  pipeline->color_blend_info = color_blend_info;
}
void VK_pipeline::create_topology(Struct_pipeline* pipeline){
  //---------------------------

  VkPipelineInputAssemblyStateCreateInfo input_assembly{};
  input_assembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
  input_assembly.primitiveRestartEnable = VK_FALSE;

  if(pipeline->topology == "point"){
    input_assembly.topology = VK_PRIMITIVE_TOPOLOGY_POINT_LIST;
  }
  else if(pipeline->topology == "line"){
    input_assembly.topology = VK_PRIMITIVE_TOPOLOGY_LINE_LIST;
  }
  else if(pipeline->topology == "triangle"){
    input_assembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
  }

  //---------------------------
  pipeline->input_assembly = input_assembly;
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
