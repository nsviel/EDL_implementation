#ifndef VK_VIEWPORT_H
#define VK_VIEWPORT_H

#include "../Struct/struct_viewport.h"
#include "../../../common.h"

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

  Struct_viewport* create_viewport_scene();
  Struct_viewport* create_viewport_canvas();

  inline VkViewport get_viewport_scene(){return viewport_scene;}
  inline VkViewport get_viewport_canvas(){return viewport_canvas;}
  inline VkRect2D get_scissor(){return scissor;}

private:
  VK_engine* vk_engine;
  VK_param* vk_param;
  Dimension* dimManager;

  VkViewport viewport_scene;
  VkViewport viewport_canvas;
  VkRect2D scissor;
};

#endif
