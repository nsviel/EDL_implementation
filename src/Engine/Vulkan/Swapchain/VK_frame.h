#ifndef VK_FRAME_H
#define VK_FRAME_H

#include "../Struct/struct_frame.h"
#include "../../../common.h"

class Engine;
class Param_vulkan;
class VK_physical_device;
class VK_texture;
class VK_synchronization;
class VK_color;
class VK_framebuffer;
class VK_swapchain;


class VK_frame
{
public:
  //Constructor / Destructor
  VK_frame(Engine* engineManager);
  ~VK_frame();

public:
  //Main function
  void init_image();
  void cleanup();

  //Creation function
  void create_frame_swapchain();
  void create_frame_inflight();

  //Deletion function
  void clean_frame_swapchain();
  void clean_frame_inflight();

private:
  Engine* engineManager;
  Param_vulkan* param_vulkan;
  VK_physical_device* vk_physical_device;
  VK_texture* vk_texture;
  VK_synchronization* vk_synchronization;
  VK_color* vk_color;
  VK_swapchain* vk_swapchain;
  VK_framebuffer* vk_framebuffer;
};

#endif
