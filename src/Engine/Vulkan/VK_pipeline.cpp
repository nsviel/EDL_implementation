#include "VK_pipeline.h"
#include "VK_device.h"
#include "VK_swapchain.h"
#include "VK_renderpass.h"
#include "VK_struct.h"
#include "Engine_vulkan.h"

#include "../Node_engine.h"


//Constructor / Destructor
VK_pipeline::VK_pipeline(Engine_vulkan* engine_vulkan){
  //---------------------------

  this->engine_vulkan = engine_vulkan;
  this->vk_device = engine_vulkan->get_vk_device();
  this->vk_swapchain = engine_vulkan->get_vk_swapchain();
  this->vk_renderpass = engine_vulkan->get_vk_renderpass();

  //---------------------------
}
VK_pipeline::~VK_pipeline(){}

//Main function
void VK_pipeline::create_graphics_pipeline(){
  VkExtent2D swapChain_extent = vk_swapchain->get_swapChain_extent();
  VkDevice device = vk_device->get_device();
  VkRenderPass renderPass = vk_renderpass->get_renderPass();
  //---------------------------

  //Compile shader from GLSL to SPIR-V
  int result_ = system("../src/Engine/Shader/glsl/compile.sh");

  //Load spir format shaders
  auto code_vert = read_file("../src/Engine/Shader/spir/vert.spv");
  auto code_frag = read_file("../src/Engine/Shader/spir/frag.spv");

  //Create associated shader modules
  VkShaderModule module_vert = create_shader_module(code_vert);
  VkShaderModule module_frag = create_shader_module(code_frag);

  //Vertex shader link in pipeline
  VkPipelineShaderStageCreateInfo info_vert{};
  info_vert.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
  info_vert.stage = VK_SHADER_STAGE_VERTEX_BIT;
  info_vert.module = module_vert;
  info_vert.pName = "main";
  info_vert.pSpecializationInfo = nullptr;

  //Fragment shader link in pipeline
  VkPipelineShaderStageCreateInfo info_frag{};
  info_frag.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
  info_frag.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
  info_frag.module = module_frag;
  info_frag.pName = "main";
  info_frag.pSpecializationInfo = nullptr;

  //Shader info array
  VkPipelineShaderStageCreateInfo shaderStages[] = {info_vert, info_frag};

  //Vertex input settings
  VkPipelineVertexInputStateCreateInfo vertexInputInfo{};
  vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
  /*vertexInputInfo.vertexBindingDescriptionCount = 0;
  vertexInputInfo.pVertexBindingDescriptions = nullptr; // Optional
  vertexInputInfo.vertexAttributeDescriptionCount = 0;
  vertexInputInfo.pVertexAttributeDescriptions = nullptr; // Optional*/

  auto bindingDescription = Vertex::getBindingDescription();
  auto attributeDescriptions = Vertex::getAttributeDescriptions();

  vertexInputInfo.vertexBindingDescriptionCount = 1;
  vertexInputInfo.vertexAttributeDescriptionCount = static_cast<uint32_t>(attributeDescriptions.size());
  vertexInputInfo.pVertexBindingDescriptions = &bindingDescription;
  vertexInputInfo.pVertexAttributeDescriptions = attributeDescriptions.data();

  //Drawing topology
  VkPipelineInputAssemblyStateCreateInfo inputAssembly{};
  inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
  inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
  inputAssembly.primitiveRestartEnable = VK_FALSE;

  //Viewport
  VkViewport viewport{};
  viewport.x = 0.0f;
  viewport.y = 0.0f;
  viewport.width  = (float) swapChain_extent.width;
  viewport.height = (float) swapChain_extent.height;
  viewport.minDepth = 0.0f;
  viewport.maxDepth = 1.0f;

  //Dynamic internal variables (viewport, line width, ...)
  //the subsequent values has to be given at runtime
  std::vector<VkDynamicState> dynamicStates = {
    VK_DYNAMIC_STATE_VIEWPORT,
    VK_DYNAMIC_STATE_SCISSOR
  };
  VkPipelineDynamicStateCreateInfo dynamicState{};
  dynamicState.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
  dynamicState.dynamicStateCount = static_cast<uint32_t>(dynamicStates.size());
  dynamicState.pDynamicStates = dynamicStates.data();

  //Full viewport scissor
  VkRect2D scissor{};
  scissor.offset = {0, 0};
  scissor.extent = swapChain_extent;

  //Viewport info
  VkPipelineViewportStateCreateInfo viewportState{};
  viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
  viewportState.viewportCount = 1;
  viewportState.scissorCount = 1;

  //Rasterization stage
  VkPipelineRasterizationStateCreateInfo rasterizer{};
  rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
  rasterizer.depthClampEnable = VK_FALSE;
  rasterizer.rasterizerDiscardEnable = VK_FALSE;
  rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
  rasterizer.lineWidth = 1.0f;
  rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
  rasterizer.frontFace = VK_FRONT_FACE_CLOCKWISE;
  rasterizer.depthBiasEnable = VK_FALSE;
  rasterizer.depthBiasConstantFactor = 0.0f; // Optional
  rasterizer.depthBiasClamp = 0.0f; // Optional
  rasterizer.depthBiasSlopeFactor = 0.0f; // Optional

  //Multisampling -> disabled
  VkPipelineMultisampleStateCreateInfo multisampling{};
  multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
  multisampling.sampleShadingEnable = VK_FALSE;
  multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
  multisampling.minSampleShading = 1.0f; // Optional
  multisampling.pSampleMask = nullptr; // Optional
  multisampling.alphaToCoverageEnable = VK_FALSE; // Optional
  multisampling.alphaToOneEnable = VK_FALSE; // Optional

  //Color blending stage
  VkPipelineColorBlendAttachmentState colorBlendAttachment{};
  colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
  colorBlendAttachment.blendEnable = VK_FALSE;
  colorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_ONE; // Optional
  colorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO; // Optional
  colorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD; // Optional
  colorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE; // Optional
  colorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO; // Optional
  colorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD; // Optional

  VkPipelineColorBlendStateCreateInfo colorBlending{};
  colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
  colorBlending.logicOpEnable = VK_FALSE;
  colorBlending.logicOp = VK_LOGIC_OP_COPY; // Optional
  colorBlending.attachmentCount = 1;
  colorBlending.pAttachments = &colorBlendAttachment;
  colorBlending.blendConstants[0] = 0.0f; // Optional
  colorBlending.blendConstants[1] = 0.0f; // Optional
  colorBlending.blendConstants[2] = 0.0f; // Optional
  colorBlending.blendConstants[3] = 0.0f; // Optional

  //Pipeline layout info -> usefull for shader uniform variables
  VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
  pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
  pipelineLayoutInfo.setLayoutCount = 0; // Optional
  pipelineLayoutInfo.pSetLayouts = nullptr; // Optional
  pipelineLayoutInfo.pushConstantRangeCount = 0; // Optional
  pipelineLayoutInfo.pPushConstantRanges = nullptr; // Optional

  //Pipeline layout creation
  VkResult result = vkCreatePipelineLayout(device, &pipelineLayoutInfo, nullptr, &pipelineLayout);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to create pipeline layout!");
  }

  //Final graphics pipeline info
  VkGraphicsPipelineCreateInfo pipelineInfo{};
  pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
  pipelineInfo.stageCount = 2;
  pipelineInfo.pStages = shaderStages;
  pipelineInfo.pVertexInputState = &vertexInputInfo;
  pipelineInfo.pInputAssemblyState = &inputAssembly;
  pipelineInfo.pViewportState = &viewportState;
  pipelineInfo.pRasterizationState = &rasterizer;
  pipelineInfo.pMultisampleState = &multisampling;
  pipelineInfo.pDepthStencilState = nullptr; // Optional
  pipelineInfo.pColorBlendState = &colorBlending;
  pipelineInfo.pDynamicState = &dynamicState;
  pipelineInfo.layout = pipelineLayout;
  pipelineInfo.renderPass = renderPass;
  pipelineInfo.subpass = 0;
  pipelineInfo.basePipelineHandle = VK_NULL_HANDLE; // Optional
  pipelineInfo.basePipelineIndex = -1; // Optional

  //Final graphics pipeline creation
  VkResult result_pipe = vkCreateGraphicsPipelines(device, VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &graphicsPipeline);
  if(result_pipe != VK_SUCCESS){
    throw std::runtime_error("[error] failed to create graphics pipeline!");
  }

  //Destroy shader modules
  vkDestroyShaderModule(device, module_vert, nullptr);
  vkDestroyShaderModule(device, module_frag, nullptr);

  //---------------------------
}
void VK_pipeline::cleanup(){
  VkDevice device = vk_device->get_device();
  //---------------------------

  vkDestroyPipeline(device, graphicsPipeline, nullptr);
  vkDestroyPipelineLayout(device, pipelineLayout, nullptr);

  //---------------------------
}

VkShaderModule VK_pipeline::create_shader_module(const std::vector<char>& code){
  //Shader modules are just a thin wrapper around the shader bytecode
  //---------------------------

  VkDevice device = vk_device->get_device();

  //Shader module info
  VkShaderModuleCreateInfo createInfo{};
  createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
  createInfo.codeSize = code.size();
  createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());

  //Shader module creation
  VkShaderModule shaderModule;
  VkResult result = vkCreateShaderModule(device, &createInfo, nullptr, &shaderModule);
  if (result != VK_SUCCESS) {
    throw std::runtime_error("[error] failed to create shader module!");
  }

  //---------------------------
  return shaderModule;
}
std::vector<char> VK_pipeline::read_file(const std::string& filename){
  std::ifstream file(filename, std::ios::ate | std::ios::binary);
  //---------------------------

  if (!file.is_open()) {
    throw std::runtime_error("[error] failed to open file!");
  }

  size_t fileSize = (size_t) file.tellg();
  std::vector<char> buffer(fileSize);

  file.seekg(0);
  file.read(buffer.data(), fileSize);

  file.close();

  //---------------------------
  return buffer;
}
