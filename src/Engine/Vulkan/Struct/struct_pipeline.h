#ifndef STRUCT_PIPELINE_H
#define STRUCT_PIPELINE_H

#include "struct_uniform.h"

#include <string>
#include <vector>
#include <vulkan/vulkan.h>


struct Struct_pipeline{
  //Info
  std::string name;
  std::string topology;

  //Pipeline shader
  bool compile_shader;
  std::string path_shader_vs;
  std::string path_shader_fs;
  Struct_uniform uniform;

  //Pipeline elments
  VkPipeline pipeline;
  VkPipelineLayout pipeline_layout;
  VkGraphicsPipelineCreateInfo pipeline_info;
  VkDescriptorSetLayout descriptor_layout;
  VkDescriptorSet descriptor_set;

  //Pipeline info elements
  std::vector<VkPipelineShaderStageCreateInfo> shader_stage;
  std::vector<VkDynamicState> dynamic_state_object;
  std::vector<VkVertexInputBindingDescription> data_description;
  std::vector<VkVertexInputAttributeDescription> attribut_description;
  std::vector<std::pair<VkShaderModule, VkShaderModule>> vec_shader_couple;
  std::vector<std::string> vec_data_name;

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
