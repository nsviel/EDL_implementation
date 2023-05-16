#include "VK_image.h"

#include "../Rendering/VK_framebuffer.h"
#include "../Rendering/VK_depth.h"
#include "../Data/VK_texture.h"
#include "../Device/VK_device.h"
#include "../Device/VK_physical_device.h"
#include "../Instance/VK_window.h"
#include "../Engine.h"

#include "../../Param_engine.h"


//Constructor / Destructor
VK_image::VK_image(Engine* engineManager){
  //---------------------------

  this->param_engine = engineManager->get_param_engine();
  this->vk_window = engineManager->get_vk_window();
  this->vk_device = engineManager->get_vk_device();
  this->vk_physical_device = engineManager->get_vk_physical_device();
  this->vk_texture = engineManager->get_vk_texture();

  //---------------------------
}
VK_image::~VK_image(){}

//Main function
void VK_image::init_image(){
  //---------------------------

  this->create_image_struct();
  this->create_image_view();

  //---------------------------
}
void VK_image::cleanup(){
  VkDevice device = vk_device->get_device();
  //---------------------------

  for(size_t i=0; i<vec_image_view.size(); i++){
    vkDestroyImageView(device, vec_image_view[i], nullptr);
  }

  //---------------------------
}

//Creation function
void VK_image::create_image_struct(){
  //---------------------------

  for(int i=0; i<param_engine->max_frame_inflight; i++){
    Image* image = new Image();
    image->image = vec_image[i];
    vec_image_obj.push_back(image);
  }

  //---------------------------
}
void VK_image::create_image_view(){
  VkDevice device = vk_device->get_device();
  VkPhysicalDevice physical_device = vk_physical_device->get_physical_device();
  //---------------------------

  vector<VkSurfaceFormatKHR> surface_format = vk_physical_device->find_surface_format(physical_device);
  VkSurfaceFormatKHR surfaceFormat = retrieve_surface_format(surface_format);
  this->image_format = surfaceFormat.format;

  //Resize the image view vector
  vec_image_view.resize(vec_image.size());

  //Image view settings & creation
  for(size_t i=0; i<vec_image.size(); i++){
    vec_image_view[i] = vk_texture->create_image_view(vec_image[i], image_format, VK_IMAGE_ASPECT_COLOR_BIT);
  }

  //---------------------------
}
void VK_image::create_image_swapchain(VkSwapchainKHR swapchain, unsigned int min_image_count){
  VkDevice device = vk_device->get_device();
  //---------------------------

  //Empty swapchain image
  vkGetSwapchainImagesKHR(device, swapchain, &min_image_count, nullptr);

  //Fill swapchain image
  vec_image.resize(min_image_count);
  vkGetSwapchainImagesKHR(device, swapchain, &min_image_count, vec_image.data());

  //---------------------------
}

//Subfunction
VkSurfaceFormatKHR VK_image::retrieve_surface_format(const std::vector<VkSurfaceFormatKHR>& dev_format){
  //---------------------------

  //Check if standar RGB is available
  for(const auto& format : dev_format){
    if(format.format == VK_FORMAT_B8G8R8A8_SRGB && format.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR){
      return format;
    }
  }

  //---------------------------
  return dev_format[0];
}
