#ifndef VK_RENDERPASS_H
#define VK_RENDERPASS_H

#include <vulkan/vulkan.h>

#include "../../../common.h"

class Engine;
class VK_device;
class VK_swapchain;
class VK_image;


class VK_renderpass
{
public:
  //Constructor / Destructor
  VK_renderpass(Engine* engineManager);
  ~VK_renderpass();

public:
  //Main functions
  void create_render_pass();
  void cleanup();

  inline VkRenderPass get_renderPass(){return renderPass;}

private:
  Engine* engineManager;
  VK_device* vk_device;
  VK_swapchain* vk_swapchain;
  VK_image* vk_image;

  VkPipelineLayout pipelineLayout;
  VkRenderPass renderPass;
};

#endif
