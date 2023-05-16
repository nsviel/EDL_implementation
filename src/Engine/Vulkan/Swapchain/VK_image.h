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
  //Creation function
  void create_image_struct();
  void create_image_view(Image* image);
  void create_image_swapchain(VkSwapchainKHR swapchain, unsigned int min_image_count);

  //Deletion function
  void clean_image_struct();
  void clean_image_view(Image* image);

  //Subfunction
  VkSurfaceFormatKHR retrieve_surface_format(const std::vector<VkSurfaceFormatKHR>& dev_format);

  inline vector<Image*> get_vec_image_obj(){return vec_image_obj;}
  inline VkFormat get_image_format(){return image_format;}
  inline void set_vec_image(vector<VkImage> value){vec_image = value;}

private:
  Engine* engineManager;
  Param_engine* param_engine;
  VK_window* vk_window;
  VK_device* vk_device;
  VK_physical_device* vk_physical_device;
  VK_texture* vk_texture;

  VkFormat image_format;
  vector<VkImage> vec_image;
  vector<Image*> vec_image_obj;
};

#endif
