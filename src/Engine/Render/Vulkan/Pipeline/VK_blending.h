#ifndef VK_BLENDING_H
#define VK_BLENDING_H

#include "../Struct/struct_pipeline.h"
#include "../Struct/struct_renderpass.h"
#include "../../Render_common.h"

class VK_engine;
class VK_param;


class VK_blending
{
public:
  //Constructor / Destructor
  VK_blending(VK_engine* vk_engine);
  ~VK_blending();

public:
  //Main functions
  void create_color_blending_state(Struct_pipeline* pipeline);
  void create_color_blending(Struct_pipeline* pipeline);

private:
  VK_engine* vk_engine;
  VK_param* vk_param;
};

#endif
