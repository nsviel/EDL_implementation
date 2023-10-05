#ifndef VK_VIEWPORT_H
#define VK_VIEWPORT_H

#include "../Struct/struct_viewport.h"
#include "../../Render_common.h"

class VK_engine;
class VK_param;
class Dimension;


class VK_viewport
{
public:
  VK_viewport(VK_engine* vk_engine);
  ~VK_viewport();

public:
  void init_viewport();
  void update_viewport();

  Struct_viewport* create_viewport();

  inline VkViewport get_viewport(){return viewport;}
  inline VkRect2D get_scissor(){return scissor;}

private:
  VK_engine* vk_engine;
  VK_param* vk_param;
  Dimension* dimManager;

  VkViewport viewport;
  VkRect2D scissor;
};

#endif
