#include "VK_pipeline.h"
#include "VK_renderpass.h"

#include "../Data/VK_descriptor.h"
#include "../Data/VK_data.h"
#include "../Engine.h"
#include "../Device/VK_device.h"
#include "../Swapchain/VK_swapchain.h"
#include "../Camera/VK_viewport.h"
#include "../Shader/VK_shader.h"

#include "../../Node_engine.h"


//Constructor / Destructor
VK_pipeline::VK_pipeline(Engine* engineManager){
  //---------------------------

  this->engineManager = engineManager;
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
void VK_pipeline::create_pipelines(){
  //---------------------------

  this->create_pipeline("point");
  this->create_pipeline("line");

  //---------------------------
}
void VK_pipeline::cleanup(){
  VkDevice device = vk_device->get_device();
  //---------------------------

  vkDestroyPipeline(device, pipeline_point, nullptr);
  vkDestroyPipelineLayout(device, pipeline_layout_point, nullptr);

  vkDestroyPipeline(device, pipeline_line, nullptr);
  vkDestroyPipelineLayout(device, pipeline_layout_line, nullptr);

  //---------------------------
}

//Pipeline creation
void VK_pipeline::create_pipeline(string topology){
  VK_data* vk_data = engineManager->get_vk_data();
  VkDevice device = vk_device->get_device();
  VkRenderPass renderPass = vk_renderpass->get_renderPass();
  //---------------------------

  //Get appropriate data
  std::vector<VkVertexInputBindingDescription> bindingDescriptions = vk_data->description_binding();
  std::vector<VkVertexInputAttributeDescription> attributeDescriptions = vk_data->description_vertex();
  std::vector<VkDynamicState> dynamicStates;
  dynamicStates.push_back(VK_DYNAMIC_STATE_VIEWPORT);
  dynamicStates.push_back(VK_DYNAMIC_STATE_SCISSOR);
  //dynamicStates.push_back(VK_DYNAMIC_STATE_POINT_SIZE);
  if(topology == "line"){
    dynamicStates.push_back(VK_DYNAMIC_STATE_LINE_WIDTH);
  }

  //Construct pipeline elements
  vk_shader->create_shader_module();
  VkShaderModule module_vert = vk_shader->get_module_vert();
  VkShaderModule module_frag = vk_shader->get_module_frag();
  vector<VkPipelineShaderStageCreateInfo> shaderStages = vk_shader->pipeline_shader_info(module_vert, module_frag);
  VkPipelineVertexInputStateCreateInfo vertexInputInfo = pipe_data_description(bindingDescriptions, attributeDescriptions);
  VkPipelineInputAssemblyStateCreateInfo inputAssembly = pipe_topology(topology);
  VkPipelineDynamicStateCreateInfo dynamicState = pipe_dynamic_state(dynamicStates);
  VkPipelineViewportStateCreateInfo viewportState = pipe_viewport();
  VkPipelineRasterizationStateCreateInfo rasterizer = pipe_raster();
  VkPipelineMultisampleStateCreateInfo multisampling = pipe_multisampling();
  VkPipelineColorBlendAttachmentState colorBlendAttachment = pipe_color_blending_state();
  VkPipelineColorBlendStateCreateInfo colorBlending = pipe_color_blending(&colorBlendAttachment);
  VkPipelineDepthStencilStateCreateInfo depthStencil = pipe_depth();
  this->create_pipeline_layout(topology);

  //Final graphics pipeline info
  VkGraphicsPipelineCreateInfo pipelineInfo{};
  pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
  pipelineInfo.stageCount = 2;
  pipelineInfo.pStages = shaderStages.data();
  pipelineInfo.pVertexInputState = &vertexInputInfo;
  pipelineInfo.pInputAssemblyState = &inputAssembly;
  pipelineInfo.pViewportState = &viewportState;
  pipelineInfo.pRasterizationState = &rasterizer;
  pipelineInfo.pMultisampleState = &multisampling;
  pipelineInfo.pDepthStencilState = &depthStencil;
  pipelineInfo.pColorBlendState = &colorBlending;
  pipelineInfo.pDynamicState = &dynamicState;
  pipelineInfo.layout = pipeline_layout_point;
  pipelineInfo.renderPass = renderPass;
  pipelineInfo.subpass = 0;
  pipelineInfo.basePipelineHandle = VK_NULL_HANDLE; // Optional
  pipelineInfo.basePipelineIndex = -1; // Optional

  //Final graphics pipeline creation
  this->create_pipeline_graphics(pipelineInfo, topology);

  //Destroy shader modules
  vkDestroyShaderModule(device, module_vert, nullptr);
  vkDestroyShaderModule(device, module_frag, nullptr);

  //---------------------------
}
void VK_pipeline::create_pipeline_graphics(VkGraphicsPipelineCreateInfo pipelineInfo, string topology){
  VkDevice device = vk_device->get_device();
  //---------------------------

  if(topology == "point"){
    VkResult result = vkCreateGraphicsPipelines(device, VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &pipeline_point);
    if(result != VK_SUCCESS){
      throw std::runtime_error("[error] failed to create graphics pipeline!");
    }
  }
  else if(topology == "line"){
    VkResult result = vkCreateGraphicsPipelines(device, VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &pipeline_line);
    if(result != VK_SUCCESS){
      throw std::runtime_error("[error] failed to create graphics pipeline!");
    }
  }

  //---------------------------
}
void VK_pipeline::create_pipeline_layout(string topology){
  VkDevice device = vk_device->get_device();
  //---------------------------

  //Pipeline layout info -> usefull for shader uniform variables
  VkDescriptorSetLayout descriptorSetLayout = vk_descriptor->get_descriptorSetLayout();
  VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
  pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
  pipelineLayoutInfo.setLayoutCount = 1;
  pipelineLayoutInfo.pSetLayouts = &descriptorSetLayout;
  pipelineLayoutInfo.pushConstantRangeCount = 0; // Optional
  pipelineLayoutInfo.pPushConstantRanges = nullptr; // Optional

  //Pipeline layout creation
  if(topology == "point"){
    VkResult result = vkCreatePipelineLayout(device, &pipelineLayoutInfo, nullptr, &pipeline_layout_point);
    if(result != VK_SUCCESS){
      throw std::runtime_error("[error] failed to create pipeline layout!");
    }
  }
  else if(topology == "line"){
    VkResult result = vkCreatePipelineLayout(device, &pipelineLayoutInfo, nullptr, &pipeline_layout_line);
    if(result != VK_SUCCESS){
      throw std::runtime_error("[error] failed to create pipeline layout!");
    }
  }

  //---------------------------
}

//Subfunction
VkPipelineVertexInputStateCreateInfo VK_pipeline::pipe_data_description(vector<VkVertexInputBindingDescription>& bindingDescriptions, vector<VkVertexInputAttributeDescription>& attributeDescriptions){
  //---------------------------

  VkPipelineVertexInputStateCreateInfo vertexInputInfo{};
  vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
  vertexInputInfo.vertexBindingDescriptionCount = static_cast<uint32_t>(bindingDescriptions.size());
  vertexInputInfo.vertexAttributeDescriptionCount = static_cast<uint32_t>(attributeDescriptions.size());
  vertexInputInfo.pVertexBindingDescriptions = bindingDescriptions.data();
  vertexInputInfo.pVertexAttributeDescriptions = attributeDescriptions.data();

  //---------------------------
  return vertexInputInfo;
}
VkPipelineDynamicStateCreateInfo VK_pipeline::pipe_dynamic_state(std::vector<VkDynamicState>& dynamicStates){
  //---------------------------

  //Dynamic internal variables (viewport, line width, ...)
  //the subsequent values has to be given at runtime
  VkPipelineDynamicStateCreateInfo dynamicState{};
  dynamicState.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
  dynamicState.dynamicStateCount = static_cast<uint32_t>(dynamicStates.size());
  dynamicState.pDynamicStates = dynamicStates.data();

  //---------------------------
  return dynamicState;
}
VkPipelineViewportStateCreateInfo VK_pipeline::pipe_viewport(){
  VkExtent2D swapchain_extent = vk_swapchain->get_swapChain_extent();
  //---------------------------

  //Viewport
  vk_viewport->update_viewport(swapchain_extent);
  VkViewport viewport = vk_viewport->get_viewport();
  VkRect2D scissor = vk_viewport->get_scissor();

  //Viewport info
  VkPipelineViewportStateCreateInfo viewportState{};
  viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
  viewportState.viewportCount = 1;
  viewportState.pViewports = &viewport;
  viewportState.scissorCount = 1;
  viewportState.pScissors = &scissor;

  //---------------------------
  return viewportState;
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

  VkPipelineDepthStencilStateCreateInfo depthStencil = {};
  depthStencil.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
  depthStencil.depthTestEnable = VK_TRUE;
  depthStencil.depthWriteEnable = VK_TRUE;
  depthStencil.depthCompareOp = VK_COMPARE_OP_LESS;
  depthStencil.depthBoundsTestEnable = VK_FALSE;
  depthStencil.minDepthBounds = 0.0f; // Optional
  depthStencil.maxDepthBounds = 1.0f; // Optional
  depthStencil.stencilTestEnable = VK_FALSE;
  depthStencil.front = {}; // Optional
  depthStencil.back = {}; // Optional

  //---------------------------
  return depthStencil;
}
VkPipelineColorBlendAttachmentState VK_pipeline::pipe_color_blending_state(){
  //---------------------------

  VkPipelineColorBlendAttachmentState colorBlendAttachment{};
  colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
  colorBlendAttachment.blendEnable = VK_FALSE;
  colorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_ONE; // Optional
  colorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO; // Optional
  colorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD; // Optional
  colorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE; // Optional
  colorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO; // Optional
  colorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD; // Optional

  //---------------------------
  return colorBlendAttachment;
}
VkPipelineColorBlendStateCreateInfo VK_pipeline::pipe_color_blending(VkPipelineColorBlendAttachmentState* colorBlendAttachment){
  //---------------------------

  VkPipelineColorBlendStateCreateInfo colorBlending{};
  colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
  colorBlending.logicOpEnable = VK_FALSE;
  colorBlending.logicOp = VK_LOGIC_OP_COPY; // Optional
  colorBlending.attachmentCount = 1;
  colorBlending.pAttachments = colorBlendAttachment;
  colorBlending.blendConstants[0] = 0.0f; // Optional
  colorBlending.blendConstants[1] = 0.0f; // Optional
  colorBlending.blendConstants[2] = 0.0f; // Optional
  colorBlending.blendConstants[3] = 0.0f; // Optional

  //---------------------------
  return colorBlending;
}
VkPipelineInputAssemblyStateCreateInfo VK_pipeline::pipe_topology(string topology){
  //---------------------------

  VkPipelineInputAssemblyStateCreateInfo inputAssembly{};
  inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
  inputAssembly.primitiveRestartEnable = VK_FALSE;

  if(topology == "point"){
    inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_POINT_LIST;
  }
  else if(topology == "line"){
    inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_LINE_LIST;
  }

  //---------------------------
  return inputAssembly;
}
