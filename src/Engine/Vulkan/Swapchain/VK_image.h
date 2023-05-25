#ifndef VK_IMAGE_H
#define VK_IMAGE_H

#include "../Struct/struct_image.h"
#include "../../../common.h"

class Engine;
class Param_vulkan;
class VK_physical_device;
class VK_texture;
class VK_synchronization;
class VK_color;
class VK_swapchain;


class VK_image
{
public:
  //Constructor / Destructor
  VK_image(Engine* engineManager);
  ~VK_image();

public:
  //Main function
  void init_image();
  void cleanup();

  //Creation function
  void create_image_struct();
  void create_frame_struct();

  //Deletion function
  void clean_frame_struct();
  void clean_image_struct();

  inline vector<Image*> get_vec_image(){return vec_image;}
  inline vector<Frame*> get_vec_frame(){return vec_frame;}

private:
  Engine* engineManager;
  Param_vulkan* param_vulkan;
  VK_physical_device* vk_physical_device;
  VK_texture* vk_texture;
  VK_synchronization* vk_synchronization;
  VK_color* vk_color;
  VK_swapchain* vk_swapchain;

  vector<Image*> vec_image;
  vector<Frame*> vec_frame;
};

#endif
