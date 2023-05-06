#ifndef VK_FRAMEBUFFER_H
#define VK_FRAMEBUFFER_H

#include <vulkan/vulkan.h>

#include "../../../common.h"

class Engine;
class VK_device;
class VK_swapchain;
class VK_renderpass;


class VK_framebuffer
{
public:
  //Constructor / Destructor
  VK_framebuffer(Engine* engineManager);
  ~VK_framebuffer();

public:
  //Main functions
  void create_framebuffers();
  void cleanup();

  inline std::vector<VkFramebuffer> get_swapChain_fbo(){return swapChain_fbo;}

private:
  Engine* engineManager;
  VK_device* vk_device;
  VK_swapchain* vk_swapchain;
  VK_renderpass* vk_renderpass;

  std::vector<VkFramebuffer> swapChain_fbo;
};

#endif
