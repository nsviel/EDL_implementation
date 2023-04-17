#ifndef VK_PIPELINE_H
#define VK_PIPELINE_H

#include <vulkan/vulkan.h>

#include "../../common.h"

class Engine_vulkan;
class VK_device;
class VK_swapchain;
class VK_renderpass;


class VK_pipeline
{
public:
  //Constructor / Destructor
  VK_pipeline(Engine_vulkan* engine_vulkan);
  ~VK_pipeline();

public:
  //Main functions
  void create_graphics_pipeline();
  void cleanup();

  VkShaderModule create_shader_module(const std::vector<char>& code);
  std::vector<char> read_file(const std::string& filename);

  inline VkPipelineLayout get_pipelineLayout(){return pipelineLayout;}
  inline VkPipeline get_graphicsPipeline(){return graphicsPipeline;}

private:
  Engine_vulkan* engine_vulkan;
  VK_device* vk_device;
  VK_swapchain* vk_swapchain;
  VK_renderpass* vk_renderpass;

  VkPipelineLayout pipelineLayout;
  VkPipeline graphicsPipeline;
};

#endif
