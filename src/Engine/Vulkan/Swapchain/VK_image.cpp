#include "VK_image.h"

#include "../Rendering/VK_framebuffer.h"
#include "../Rendering/VK_depth.h"
#include "../Data/VK_texture.h"
#include "../Device/VK_device.h"
#include "../Device/VK_physical_device.h"
#include "../Instance/VK_window.h"
#include "../Engine.h"


//Constructor / Destructor
VK_image::VK_image(Engine* engineManager){
  //---------------------------

  this->engineManager = engineManager;
  this->vk_window = engineManager->get_vk_window();
  this->vk_device = engineManager->get_vk_device();
  this->vk_physical_device = engineManager->get_vk_physical_device();
  this->vk_texture = engineManager->get_vk_texture();

  //---------------------------
}
VK_image::~VK_image(){}

//Main function
void VK_image::create_image_views(){
  VkDevice device = vk_device->get_device();
  VK_texture* vk_texture = engineManager->get_vk_texture();
  //---------------------------

  //Resize the image view vector
  vec_image_view.resize(vec_image.size());

  //Image view settings & creation
  for(size_t i=0; i<vec_image.size(); i++){
    vec_image_view[i] = vk_texture->create_image_view(vec_image[i], image_format, VK_IMAGE_ASPECT_COLOR_BIT);
  }

  //---------------------------
}
