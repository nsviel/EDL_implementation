#ifndef VK_FRAMEBUFFER_H
#define VK_FRAMEBUFFER_H

#include "../../Struct/struct_frame.h"
#include "../../../../common.h"

class VK_engine;
class VK_param;
class VK_renderpass;


class VK_framebuffer
{
public:
  //Constructor / Destructor
  VK_framebuffer(VK_engine* vk_engine);
  ~VK_framebuffer();

public:
  //FBO creation
  void create_framebuffer(Frame_renderpass* image);

  //Deletion functions
  void clean_framebuffer(Frame_renderpass* image);

private:
  VK_param* vk_param;
  VK_renderpass* vk_renderpass;
};

#endif
