#ifndef VK_FRAMEBUFFER_H
#define VK_FRAMEBUFFER_H

#include "../Struct/struct_frame.h"
#include "../Struct/struct_renderpass.h"
#include "../../Render_common.h"

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
  void create_framebuffer(Struct_renderpass* renderpass, Frame* image);

  //Deletion functions
  void clean_framebuffer(Frame* image);

private:
  VK_param* vk_param;
  VK_renderpass* vk_renderpass;
};

#endif
