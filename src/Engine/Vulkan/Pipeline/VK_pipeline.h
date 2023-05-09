#ifndef VK_PIPELINE_H
#define VK_PIPELINE_H

#include <vulkan/vulkan.h>

#include "../../../common.h"

class Engine;
class VK_device;
class VK_swapchain;
class VK_renderpass;
class VK_descriptor;
class VK_viewport;
class VK_shader;


class VK_pipeline
{
public:
  //Constructor / Destructor
  VK_pipeline(Engine* engineManager);
  ~VK_pipeline();

public:
  //Main functions
  void create_pipelines();
  void cleanup();

  //Pipeline creation
  void create_pipeline(string topology);
  void create_pipeline_graphics(VkGraphicsPipelineCreateInfo pipelineInfo, string topology);
  void create_pipeline_layout(string topology);

  //Subfunction
  VkPipelineVertexInputStateCreateInfo pipe_data_description(vector<VkVertexInputBindingDescription>& bindingDescriptions, vector<VkVertexInputAttributeDescription>& attributeDescriptions);
  VkPipelineDynamicStateCreateInfo pipe_dynamic_state(std::vector<VkDynamicState>& dynamicStates);
  VkPipelineViewportStateCreateInfo pipe_viewport();
  VkPipelineRasterizationStateCreateInfo pipe_raster();
  VkPipelineMultisampleStateCreateInfo pipe_multisampling();
  VkPipelineDepthStencilStateCreateInfo pipe_depth();
  VkPipelineColorBlendAttachmentState pipe_color_blending_state();
  VkPipelineColorBlendStateCreateInfo pipe_color_blending(VkPipelineColorBlendAttachmentState* colorBlendAttachment);
  VkPipelineInputAssemblyStateCreateInfo pipe_topology(string topology);

  inline VkPipelineLayout get_pipeline_layout_point(){return pipeline_layout_point;}
  inline VkPipelineLayout get_pipeline_layout_line(){return pipeline_layout_line;}
  inline VkPipeline get_pipeline_point(){return pipeline_point;}
  inline VkPipeline get_pipeline_line(){return pipeline_line;}

private:
  Engine* engineManager;
  VK_device* vk_device;
  VK_swapchain* vk_swapchain;
  VK_renderpass* vk_renderpass;
  VK_descriptor* vk_descriptor;
  VK_viewport* vk_viewport;
  VK_shader* vk_shader;

  VkPipelineLayout pipeline_layout_point;
  VkPipelineLayout pipeline_layout_line;
  VkPipeline pipeline_point;
  VkPipeline pipeline_line;
};

#endif
