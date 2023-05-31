#ifndef VK_FRAMEBUFFER_H
#define VK_FRAMEBUFFER_H

#include "../Struct/struct_frame.h"
#include "../../../common.h"

class VK_engine;
class Param_vulkan;
class VK_renderpass;


class VK_framebuffer
{
public:
  //Constructor / Destructor
  VK_framebuffer(VK_engine* vk_engine);
  ~VK_framebuffer();

public:
  //FBO creation
  void create_framebuffer(Frame_swapchain* image);

  //Deletion functions
  void clean_framebuffer(Frame_swapchain* image);

private:
  Param_vulkan* param_vulkan;
  VK_renderpass* vk_renderpass;
};

#endif
