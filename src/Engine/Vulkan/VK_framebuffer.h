#ifndef VK_FRAMEBUFFER_H
#define VK_FRAMEBUFFER_H

#include <vulkan/vulkan.h>

#include "../../common.h"

class Engine_vulkan;


class VK_framebuffer
{
public:
  //Constructor / Destructor
  VK_framebuffer(Engine_vulkan* engine_vulkan);
  ~VK_framebuffer();

public:
  //Main functions
  void create_framebuffers();

  inline std::vector<VkFramebuffer> get_swapChain_fbo(){return swapChain_fbo;}

private:
  Engine_vulkan* engine_vulkan;

  std::vector<VkFramebuffer> swapChain_fbo;
};

#endif
