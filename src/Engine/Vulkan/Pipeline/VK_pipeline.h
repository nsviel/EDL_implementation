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


class VK_pipeline
{
public:
  //Constructor / Destructor
  VK_pipeline(Engine* engineManager);
  ~VK_pipeline();

public:
  //Main functions
  void create_graphics_pipeline();
  void cleanup();

  VkShaderModule create_shader_module(const std::vector<char>& code);
  std::vector<char> read_file(const std::string& filename);
  vector<VkPipelineShaderStageCreateInfo> pipeline_shader_info(VkShaderModule module_vert, VkShaderModule module_frag);

  inline VkPipelineLayout get_pipelineLayout(){return pipelineLayout;}
  inline VkPipeline get_graphicsPipeline(){return graphicsPipeline;}

private:
  Engine* engineManager;
  VK_device* vk_device;
  VK_swapchain* vk_swapchain;
  VK_renderpass* vk_renderpass;
  VK_descriptor* vk_descriptor;
  VK_viewport* vk_viewport;

  VkPipelineLayout pipelineLayout;
  VkPipeline graphicsPipeline;
};

#endif
