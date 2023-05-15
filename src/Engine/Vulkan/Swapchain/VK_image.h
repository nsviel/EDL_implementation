#ifndef VK_IMAGE_H
#define VK_IMAGE_H

#include "../../../common.h"

class Engine;
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
  void create_image_views();

  inline VkFormat get_swapChain_image_format(){return image_format;}
  inline std::vector<VkImage> get_swapChain_images(){return vec_image;}
  inline std::vector<VkImageView> get_swapChain_image_views(){return vec_image_view;}

private:
  Engine* engineManager;
  VK_window* vk_window;
  VK_device* vk_device;
  VK_physical_device* vk_physical_device;
  VK_texture* vk_texture;

  VkFormat image_format;
  std::vector<VkImage> vec_image;
  std::vector<VkImageView> vec_image_view;
};

#endif
