#ifndef VK_VIEWPORT_H
#define VK_VIEWPORT_H

#include "../../../common.h"

class Engine_vulkan;
class Dimension;


class VK_viewport
{
public:
  VK_viewport(Engine_vulkan* engine_vulkan);
  ~VK_viewport();

public:
  void update_viewport(VkExtent2D swapchain_extent);

  inline VkViewport get_viewport(){return viewport;}
  inline VkRect2D get_scissor(){return scissor;}

private:
  Dimension* dimManager;

  VkViewport viewport;
  VkRect2D scissor;
};

#endif
