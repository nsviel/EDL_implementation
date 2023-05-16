#ifndef VK_IMAGE_H
#define VK_IMAGE_H

#include "../Struct/struct_image.h"
#include "../../../common.h"

class Engine;
class Param_engine;
class VK_window;
class VK_device;
class VK_physical_device;
class VK_texture;


class VK_image
{
public:
  //Constructor / Destructor
  VK_image(Engine* engineManager);
  ~VK_image();

public:
  //Main functions
  void init_image();
  void cleanup();

  //Creation function
  void create_image_struct();
  void create_image_view();
  void create_image_swapchain(VkSwapchainKHR swapchain, unsigned int min_image_count);

  //Subfunction
  VkSurfaceFormatKHR retrieve_surface_format(const std::vector<VkSurfaceFormatKHR>& dev_format);

  inline VkFormat get_image_format(){return image_format;}
  inline std::vector<VkImageView> get_swapChain_image_views(){return vec_image_view;}
  inline void set_vec_image(vector<VkImage> value){vec_image = value;}

private:
  Param_engine* param_engine;
  VK_window* vk_window;
  VK_device* vk_device;
  VK_physical_device* vk_physical_device;
  VK_texture* vk_texture;

  VkFormat image_format;
  vector<VkImage> vec_image;
  vector<VkImageView> vec_image_view;
  vector<Image*> vec_image_obj;
};

#endif
