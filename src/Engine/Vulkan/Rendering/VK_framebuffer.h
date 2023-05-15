#ifndef VK_FRAMEBUFFER_H
#define VK_FRAMEBUFFER_H

#include "../../../common.h"

class Engine;
class VK_device;
class VK_swapchain;
class VK_renderpass;
class VK_depth;
class VK_image;


class VK_framebuffer
{
public:
  //Constructor / Destructor
  VK_framebuffer(Engine* engineManager);
  ~VK_framebuffer();

public:
  //Main functions
  void init_fbo();
  void cleanup();

  //FBO creation
  void create_framebuffers();

  inline std::vector<VkFramebuffer> get_fbo_vec(){return fbo_vec;}

private:
  Engine* engineManager;
  VK_device* vk_device;
  VK_swapchain* vk_swapchain;
  VK_renderpass* vk_renderpass;
  VK_depth* vk_depth;
  VK_image* vk_image;

  std::vector<VkFramebuffer> fbo_vec;
};

#endif
