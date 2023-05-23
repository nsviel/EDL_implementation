#ifndef VK_DRAWING_H
#define VK_DRAWING_H

#include "../../../common.h"

class Engine;
class Param_vulkan;
class VK_window;
class VK_swapchain;
class VK_framebuffer;
class VK_command;
class VK_device;
class VK_uniform;
class VK_image;


class VK_drawing
{
public:
  //Constructor / Destructor
  VK_drawing(Engine* engineManager);
  ~VK_drawing();

public:
  //Main functions
  void draw_frame();
  void draw_swapchain();
  void draw_command();
  void draw_queue();

  inline uint32_t get_current_frame(){return frame_current;}

private:
  Engine* engineManager;
  Param_vulkan* param_vulkan;
  VK_window* vk_window;
  VK_swapchain* vk_swapchain;
  VK_framebuffer* vk_framebuffer;
  VK_command* vk_command;
  VK_device* vk_device;
  VK_uniform* vk_uniform;
  VK_image* vk_image;

  bool framebufferResized;
  uint32_t image_index;
  uint32_t frame_current;
};

#endif
