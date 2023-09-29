#ifndef STRUCT_PIPELINE_H
#define STRUCT_PIPELINE_H

#include "typedef.h"
#include "struct_binding.h"
#include "../../../common.h"


struct Struct_pipeline_info{
  //---------------------------

  VkGraphicsPipelineCreateInfo info;

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

  //---------------------------
};

struct Struct_pipeline{
  //---------------------------

  //Info
  std::string name = "";
  std::string topology = "";

  //Pipeline shader
  bool compile_shader = false;
  std::string path_shader_vs = "";
  std::string path_shader_fs = "";
  Struct_binding binding;

  //Pipeline elments
  VkPipeline pipeline;
  VkPipelineLayout layout;
  Struct_pipeline_info info;

  //---------------------------
};


#endif
