#ifndef VK_IMAGE_H
#define VK_IMAGE_H

#include "../Struct/struct_image.h"
#include "../../../common.h"

class Engine;
class Param_vulkan;
class VK_window;
class VK_device;
class VK_physical_device;
class VK_texture;
class VK_synchronization;


class VK_image
{
public:
  //Constructor / Destructor
  VK_image(Engine* engineManager);
  ~VK_image();

public:
  //Creation function
  void create_image_struct();
  void create_image_view(Image* image);
  void create_image_swapchain(VkSwapchainKHR swapchain, unsigned int min_image_count);

  //Deletion function
  void clean_frame_struct();
  void clean_image_struct();
  void clean_image_view(Image* image);

  //Subfunction
  VkSurfaceFormatKHR retrieve_surface_format(const std::vector<VkSurfaceFormatKHR>& dev_format);

  inline vector<Image*> get_vec_image(){return vec_image;}
  inline vector<Frame*> get_vec_frame(){return vec_frame;}
  inline VkFormat get_image_format(){return image_format;}

private:
  Engine* engineManager;
  Param_vulkan* param_vulkan;
  VK_window* vk_window;
  VK_device* vk_device;
  VK_physical_device* vk_physical_device;
  VK_texture* vk_texture;
  VK_synchronization* vk_synchronization;

  VkFormat image_format;
  vector<VkImage> vec_image_swapchain;
  vector<Image*> vec_image;
  vector<Frame*> vec_frame;
};

#endif
