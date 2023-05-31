#ifndef VK_DRAWING_H
#define VK_DRAWING_H

#include "../../../../common.h"

class VK_engine;
class VK_param;
class VK_window;
class VK_swapchain;
class VK_command;


class VK_drawing
{
public:
  //Constructor / Destructor
  VK_drawing(VK_engine* vk_engine);
  ~VK_drawing();

public:
  //Main functions
  void draw_frame();

  //Subfunction
  void acquire_next_image();
  void record_command();
  void submit_command();
  void submit_presentation();

private:
  VK_engine* vk_engine;
  VK_param* vk_param;
  VK_window* vk_window;
  VK_swapchain* vk_swapchain;
  VK_command* vk_command;
};

#endif
