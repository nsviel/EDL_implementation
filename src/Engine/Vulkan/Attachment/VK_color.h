#ifndef VK_COLOR_H
#define VK_COLOR_H

#include "../Struct/struct_frame.h"
#include "../../../common.h"

class Engine;
class Param_vulkan;
class VK_physical_device;
class VK_texture;


class VK_color
{
public:
  //Constructor / Destructor
  VK_color(Engine* engineManager);
  ~VK_color();

public:
  //Main functions
  void create_color_attachment(Frame_swapchain* image);
  void clean_color_attachment(Frame_swapchain* image);

  //Subfunction
  VkSurfaceFormatKHR retrieve_surface_format(const std::vector<VkSurfaceFormatKHR>& dev_format);
  VkFormat find_color_format();


private:
  Engine* engineManager;
  Param_vulkan* param_vulkan;
  VK_physical_device* vk_physical_device;
  VK_texture* vk_texture;

  vector<VkImage> vec_image_swapchain;
  vector<Frame_swapchain*> vec_image;
  vector<Frame_inflight*> vec_frame;
};

#endif
