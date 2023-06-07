#ifndef VK_VIEWPORT_H
#define VK_VIEWPORT_H

#include "../../../../common.h"

class VK_engine;
class Dimension;


class VK_viewport
{
public:
  VK_viewport(VK_engine* vk_engine);
  ~VK_viewport();

public:
  void update_viewport(VkExtent2D swapchain_extent);

  inline VkViewport get_viewport(){return viewport;}
  inline VkViewport get_viewport_canvas(){return viewport_canvas;}
  inline VkRect2D get_scissor(){return scissor;}

private:
  Dimension* dimManager;

  VkViewport viewport;
  VkViewport viewport_canvas;
  VkRect2D scissor;
};

#endif
