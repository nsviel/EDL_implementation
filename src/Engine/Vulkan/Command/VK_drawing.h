#ifndef VK_DRAWING_H
#define VK_DRAWING_H

#include "../../../common.h"

class VK_engine;
class Param_vulkan;
class VK_window;
class VK_swapchain;
class VK_framebuffer;
class VK_command;
class VK_device;
class VK_uniform;
class VK_frame;


class VK_drawing
{
public:
  //Constructor / Destructor
  VK_drawing(VK_engine* vk_engine);
  ~VK_drawing();

public:
  //Main functions
  void draw_frame();
  void draw_swapchain();
  void draw_command();
  void draw_queue();
  void draw_presentation();

private:
  VK_engine* vk_engine;
  Param_vulkan* param_vulkan;
  VK_window* vk_window;
  VK_swapchain* vk_swapchain;
  VK_framebuffer* vk_framebuffer;
  VK_command* vk_command;
  VK_device* vk_device;
  VK_uniform* vk_uniform;
  VK_frame* vk_frame;
};

#endif
