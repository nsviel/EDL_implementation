#include "VK_pipeline.h"

#include "../../VK_engine.h"
#include "../../VK_param.h"
#include "../../Render/Binding/VK_descriptor.h"
#include "../../Data/VK_data.h"
#include "../../Presentation/Camera/VK_viewport.h"
#include "../../Render/Shader/VK_shader.h"
#include "../../Render/Binding/VK_binding.h"


//Constructor / Destructor
VK_pipeline::VK_pipeline(VK_engine* vk_engine){
  //---------------------------

  this->vk_engine = vk_engine;
  this->vk_param = vk_engine->get_vk_param();
  this->vk_descriptor = vk_engine->get_vk_descriptor();
  this->vk_viewport = vk_engine->get_vk_viewport();
  this->vk_shader = vk_engine->get_vk_shader();
  this->vk_data = vk_engine->get_vk_data();
  this->vk_binding = vk_engine->get_vk_binding();

  //---------------------------
}
VK_pipeline::~VK_pipeline(){}

//Main function
void VK_pipeline::clean_pipeline(Struct_renderpass* renderpass){
  //---------------------------

  for(int i=0; i<renderpass->vec_pipeline.size(); i++){
    Struct_pipeline* pipeline = renderpass->vec_pipeline[i];
    vkDestroyPipeline(vk_param->device.device, pipeline->pipeline, nullptr);
    vkDestroyPipelineLayout(vk_param->device.device, pipeline->layout, nullptr);
    vk_binding->clean_binding(&pipeline->binding);
  }

  //---------------------------
}

//Pipeline creation
void VK_pipeline::create_pipeline(Struct_renderpass* renderpass){
  //---------------------------

  for(int i=0; i<renderpass->vec_pipeline.size(); i++){
    Struct_pipeline* pipeline = renderpass->vec_pipeline[i];
    this->create_pipeline_graphics(pipeline, renderpass);
    vk_binding->create_binding(&pipeline->binding);
  }

  //---------------------------
}
void VK_pipeline::create_pipeline_graphics(Struct_pipeline* pipeline, Struct_renderpass* renderpass){
  //---------------------------

  //Dynamic
  pipeline->info.dynamic_state_object.push_back(VK_DYNAMIC_STATE_VIEWPORT);
  pipeline->info.dynamic_state_object.push_back(VK_DYNAMIC_STATE_SCISSOR);
  pipeline->info.dynamic_state_object.push_back(VK_DYNAMIC_STATE_LINE_WIDTH);

  //Pipeline elements
  this->check_struct_pipeline_input(pipeline);
  vk_descriptor->create_layout_from_required(&pipeline->binding);
  vk_shader->create_pipeline_shader(pipeline);
  vk_data->create_data_description(pipeline);
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
  pipeline_info.stageCount = static_cast<uint32_t>(pipeline->info.shader_stage.size());
  pipeline_info.pStages = pipeline->info.shader_stage.data();
  pipeline_info.pVertexInputState = &pipeline->info.vertex_input_info;
  pipeline_info.pInputAssemblyState = &pipeline->info.input_assembly;
  pipeline_info.pViewportState = &pipeline->info.viewport_state;
  pipeline_info.pRasterizationState = &pipeline->info.rasterizer;
  pipeline_info.pMultisampleState = &pipeline->info.multisampling;
  pipeline_info.pDepthStencilState = &pipeline->info.depth_stencil;
  pipeline_info.pColorBlendState = &pipeline->info.color_blend_info;
  pipeline_info.pDynamicState = &pipeline->info.dynamic_state;
  pipeline_info.layout = pipeline->layout;
  pipeline_info.renderPass = renderpass->renderpass;
  pipeline_info.subpass = 0;
  pipeline_info.basePipelineHandle = VK_NULL_HANDLE; // Optional
  pipeline_info.basePipelineIndex = -1; // Optional

  //Create pipeline graphics
  VkResult result = vkCreateGraphicsPipelines(vk_param->device.device, VK_NULL_HANDLE, 1, &pipeline_info, nullptr, &pipeline->pipeline);
  if(result != VK_SUCCESS){
      throw std::runtime_error("[error] failed to create graphics pipeline!");
    }

  //Destroy shader modules
  for(int i=0; i<pipeline->info.vec_shader_couple.size(); i++){
    pair<VkShaderModule, VkShaderModule> shader_couple = pipeline->info.vec_shader_couple[i];
    vkDestroyShaderModule(vk_param->device.device, shader_couple.first, nullptr);
    vkDestroyShaderModule(vk_param->device.device, shader_couple.second, nullptr);
  }

  //---------------------------
  pipeline->info.info = pipeline_info;
}
void VK_pipeline::create_pipeline_layout(Struct_pipeline* pipeline){
  //---------------------------

  //Push constant for MVP matrix
  /*VkPushConstantRange pushconstant_range = {};
  pushconstant_range.stageFlags = STAGE_VS;
  pushconstant_range.offset = 0;
  pushconstant_range.size = sizeof(glm::mat4);*/

  //Pipeline layout info -> usefull for shader uniform variables
  VkPipelineLayoutCreateInfo pipeline_layout_info{};
  pipeline_layout_info.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
  pipeline_layout_info.setLayoutCount = 1;
  pipeline_layout_info.pSetLayouts = &pipeline->binding.descriptor.layout;
  //pipeline_layout_info.pushConstantRangeCount = 1;
  //pipeline_layout_info.pPushConstantRanges = &pushconstant_range;

  //Pipeline layout creation
  VkResult result = vkCreatePipelineLayout(vk_param->device.device, &pipeline_layout_info, nullptr, &pipeline->layout);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to create pipeline layout!");
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
  dynamic_state.dynamicStateCount = static_cast<uint32_t>(pipeline->info.dynamic_state_object.size());
  dynamic_state.pDynamicStates = pipeline->info.dynamic_state_object.data();

  //---------------------------
  pipeline->info.dynamic_state = dynamic_state;
}
void VK_pipeline::create_viewport(Struct_pipeline* pipeline){
  //---------------------------

  //Viewport
  vk_viewport->update_viewport(vk_param->window.extent);
  VkViewport viewport = vk_viewport->get_viewport_scene();
  VkRect2D scissor = vk_viewport->get_scissor();

  //Viewport info
  VkPipelineViewportStateCreateInfo viewport_state{};
  viewport_state.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
  viewport_state.viewportCount = 1;
  viewport_state.pViewports = &viewport;
  viewport_state.scissorCount = 1;
  viewport_state.pScissors = &scissor;

  //---------------------------
  pipeline->info.viewport_state = viewport_state;
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
  pipeline->info.rasterizer = rasterizer;
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
  pipeline->info.multisampling = multisampling;
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
  pipeline->info.depth_stencil = depth_stencil;
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

  pipeline->info.color_blend_attachment = color_blend_attachment;
}
void VK_pipeline::create_color_blending(Struct_pipeline* pipeline){
  //---------------------------

  VkPipelineColorBlendStateCreateInfo color_blend_info{};
  color_blend_info.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
  color_blend_info.logicOpEnable = VK_FALSE;
  color_blend_info.logicOp = VK_LOGIC_OP_COPY; // Optional
  color_blend_info.attachmentCount = 1;
  color_blend_info.pAttachments = &pipeline->info.color_blend_attachment;
  color_blend_info.blendConstants[0] = 0.0f; // Optional
  color_blend_info.blendConstants[1] = 0.0f; // Optional
  color_blend_info.blendConstants[2] = 0.0f; // Optional
  color_blend_info.blendConstants[3] = 0.0f; // Optional

  //---------------------------
  pipeline->info.color_blend_info = color_blend_info;
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
  pipeline->info.input_assembly = input_assembly;
}

//Subfunction
void VK_pipeline::check_struct_pipeline_input(Struct_pipeline* pipeline){
  //---------------------------

  if(pipeline->name == "") cout<<"[error] Pipeline init input -> no name"<<endl;
  if(pipeline->topology == "") cout<<"[error] Pipeline init input -> no topology"<<endl;
  if(pipeline->path_shader_vs == "") cout<<"[error] Pipeline init input -> no path_shader_vs"<<endl;
  if(pipeline->path_shader_fs == "") cout<<"[error] Pipeline init input -> no path_shader_fs"<<endl;
  if(pipeline->info.vec_data_name.size() == 0) cout<<"[error] Pipeline init input -> no vec_data_name"<<endl;
  if(pipeline->binding.vec_required_binding.size() == 0) cout<<"[error] Pipeline init input -> no vec_required_binding"<<endl;

  //---------------------------
}
Struct_pipeline* VK_pipeline::get_pipeline_byName(Struct_renderpass* renderpass, string name){
  //---------------------------

  for(int i=0; i<renderpass->vec_pipeline.size(); i++){
    Struct_pipeline* pipeline = renderpass->vec_pipeline[i];
    if(pipeline->name == name){
      return pipeline;
    }
  }

  //Error barrier
  cout<<"[error] Pipeline by name error -> not found"<<endl;
  for(int i=0; i<renderpass->vec_pipeline.size(); i++){
    Struct_pipeline* pipeline = renderpass->vec_pipeline[i];
    cout<<pipeline->name<<endl;
  }

  //---------------------------
  return nullptr;
}
