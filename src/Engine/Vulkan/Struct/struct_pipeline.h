#ifndef STRUCT_PIPELINE_H
#define STRUCT_PIPELINE_H

#include <string>
#include <vector>
#include <vulkan/vulkan.h>


struct Struct_pipeline{
  //Info
  std::string name;
  std::string topology;

  //Pipeline elments
  VkPipeline pipeline;
  VkPipelineLayout pipeline_layout;
  VkGraphicsPipelineCreateInfo pipeline_info;

  //Pipeline info elements
  std::vector<VkShaderModule> vec_shader_module;
  std::vector<VkPipelineShaderStageCreateInfo> shader_stage;
  std::vector<VkDynamicState> dynamic_state_object;
  std::vector<VkVertexInputBindingDescription> data_description;
  std::vector<VkVertexInputAttributeDescription> attribut_description;

  VkPipelineVertexInputStateCreateInfo vertex_input_info;
  VkPipelineInputAssemblyStateCreateInfo input_assembly;
  VkPipelineViewportStateCreateInfo viewport_state;
  VkPipelineRasterizationStateCreateInfo rasterizer;
  VkPipelineMultisampleStateCreateInfo multisampling;
  VkPipelineDepthStencilStateCreateInfo depth_stencil;
  VkPipelineColorBlendStateCreateInfo color_blend_info;
  VkPipelineColorBlendAttachmentState color_blend_attachment;
  VkPipelineDynamicStateCreateInfo dynamic_state;
};


#endif
