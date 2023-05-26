#ifndef VK_FRAMEBUFFER_H
#define VK_FRAMEBUFFER_H

#include "../Struct/struct_image.h"
#include "../../../common.h"

class Engine;
class Param_vulkan;
class VK_renderpass;


class VK_framebuffer
{
public:
  //Constructor / Destructor
  VK_framebuffer(Engine* engineManager);
  ~VK_framebuffer();

public:
  //FBO creation
  void create_framebuffer(Image* image);

  //Deletion functions
  void clean_framebuffer(Image* image);

private:
  Param_vulkan* param_vulkan;
  VK_renderpass* vk_renderpass;
};

#endif
