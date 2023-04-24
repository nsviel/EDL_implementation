#ifndef VK_DRAWING_H
#define VK_DRAWING_H

#include <vulkan/vulkan.h>

#include "../../common.h"

class Engine_vulkan;
class VK_window;
class VK_swapchain;
class VK_synchronization;
class VK_framebuffer;
class VK_command;
class VK_device;
class VK_uniform;


class VK_drawing
{
public:
  //Constructor / Destructor
  VK_drawing(Engine_vulkan* engine_vulkan);
  ~VK_drawing();

public:
  //Main functions
  void draw_frame();

private:
  Engine_vulkan* engine_vulkan;
  VK_window* vk_window;
  VK_swapchain* vk_swapchain;
  VK_synchronization* vk_synchronization;
  VK_framebuffer* vk_framebuffer;
  VK_command* vk_command;
  VK_device* vk_device;
  VK_uniform* vk_uniform;
};

#endif
