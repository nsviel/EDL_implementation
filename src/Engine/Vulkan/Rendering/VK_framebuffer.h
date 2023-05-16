#ifndef VK_FRAMEBUFFER_H
#define VK_FRAMEBUFFER_H

#include "../Struct/struct_image.h"
#include "../../../common.h"

class Engine;
class Param_engine;
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
  void clean_framebuffer(Image* image);

  //FBO creation
  void create_framebuffers();
  void create_framebuffer(Image* image);

private:
  Param_engine* param_engine;
  VK_device* vk_device;
  VK_swapchain* vk_swapchain;
  VK_renderpass* vk_renderpass;
  VK_depth* vk_depth;
  VK_image* vk_image;

  vector<VkFramebuffer> fbo_vec;
};

#endif
