#ifndef VK_DRAWING_H
#define VK_DRAWING_H

#include "../../../common.h"

class Engine;
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
  VK_drawing(Engine* engineManager);
  ~VK_drawing();

public:
  //Main functions
  void draw_frame();
  void draw_swapchain();
  void draw_command();
  void draw_queue();

private:
  Engine* engineManager;
  VK_window* vk_window;
  VK_swapchain* vk_swapchain;
  VK_synchronization* vk_synchronization;
  VK_framebuffer* vk_framebuffer;
  VK_command* vk_command;
  VK_device* vk_device;
  VK_uniform* vk_uniform;

  uint32_t imageIndex;
  bool framebufferResized;
};

#endif
