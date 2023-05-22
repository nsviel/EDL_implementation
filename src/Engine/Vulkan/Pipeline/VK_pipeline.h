#ifndef VK_PIPELINE_H
#define VK_PIPELINE_H

#include "../Struct/struct_pipeline.h"
#include "../../../common.h"

class Engine;
class Param_vulkan;
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
  void init_pipeline();
  void cleanup();

  //Pipeline creation
  void create_pipeline_info(string name, string topology, bool compile_shader);
  void create_pipeline_layout(Struct_pipeline* pipeline);
  void create_pipeline_graphics();

  //Pipeline element
  VkPipelineVertexInputStateCreateInfo pipe_data_description(vector<VkVertexInputBindingDescription>& bindingDescriptions, vector<VkVertexInputAttributeDescription>& attributeDescriptions);
  VkPipelineDynamicStateCreateInfo pipe_dynamic_state(std::vector<VkDynamicState>& dynamic_state);
  VkPipelineViewportStateCreateInfo pipe_viewport();
  VkPipelineRasterizationStateCreateInfo pipe_raster();
  VkPipelineMultisampleStateCreateInfo pipe_multisampling();
  VkPipelineDepthStencilStateCreateInfo pipe_depth();
  VkPipelineColorBlendAttachmentState pipe_color_blending_state();
  VkPipelineColorBlendStateCreateInfo pipe_color_blending(VkPipelineColorBlendAttachmentState* color_blend_attachment);
  VkPipelineInputAssemblyStateCreateInfo pipe_topology(string topology);

  //Subfunction
  Struct_pipeline* get_pipeline_byName(string name);

private:
  Engine* engineManager;
  Param_vulkan* param_vulkan;
  VK_device* vk_device;
  VK_swapchain* vk_swapchain;
  VK_renderpass* vk_renderpass;
  VK_descriptor* vk_descriptor;
  VK_viewport* vk_viewport;
  VK_shader* vk_shader;

  vector<Struct_pipeline*> vec_pipeline;
};

#endif
