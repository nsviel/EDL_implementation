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

  this->engineManager = engineManager;
  this->param_engine = engineManager->get_param_engine();
  this->vk_window = engineManager->get_vk_window();
  this->vk_device = engineManager->get_vk_device();
  this->vk_physical_device = engineManager->get_vk_physical_device();
  this->vk_texture = engineManager->get_vk_texture();

  //---------------------------
}
VK_image::~VK_image(){}

//Creation function
void VK_image::create_image_struct(){
  VK_depth* vk_depth = engineManager->get_vk_depth();
  VK_framebuffer* vk_framebuffer = engineManager->get_vk_framebuffer();
  //---------------------------

  //Swapchain images
  for(int i=0; i<vec_image_swapchain.size(); i++){
    Image* image = new Image();
    image->image = vec_image_swapchain[i];
    this->create_image_view(image);
    vk_depth->create_depth_resource(image);
    vec_image.push_back(image);
  }

  VK_synchronization* vk_synchronization = engineManager->get_vk_synchronization();

  //Draw frames
  for(int i=0; i<param_engine->max_frame; i++){
    Frame* frame = new Frame();
    vec_frame.push_back(frame);
  }

  //---------------------------
}
void VK_image::create_image_view(Image* image){
  VkDevice device = vk_device->get_device();
  VkPhysicalDevice physical_device = vk_physical_device->get_physical_device();
  //---------------------------

  vector<VkSurfaceFormatKHR> surface_format = vk_physical_device->find_surface_format(physical_device);
  VkSurfaceFormatKHR surfaceFormat = retrieve_surface_format(surface_format);
  this->image_format = surfaceFormat.format;

  //Image view settings & creation
  image->image_view = vk_texture->create_image_view(image->image, image_format, VK_IMAGE_ASPECT_COLOR_BIT);

  //---------------------------
}
void VK_image::create_image_swapchain(VkSwapchainKHR swapchain, unsigned int min_image_count){
  VkDevice device = vk_device->get_device();
  //---------------------------

  //Empty swapchain image
  vkGetSwapchainImagesKHR(device, swapchain, &min_image_count, nullptr);

  //Fill swapchain image
  vec_image_swapchain.resize(min_image_count);
  vkGetSwapchainImagesKHR(device, swapchain, &min_image_count, vec_image_swapchain.data());

  //---------------------------
}

//Deletio function
void VK_image::clean_image_struct(){
  VK_depth* vk_depth = engineManager->get_vk_depth();
  VK_framebuffer* vk_framebuffer = engineManager->get_vk_framebuffer();
  //---------------------------

  for(int i=0; i<vec_image.size(); i++){
    Image* image = vec_image[i];

    this->clean_image_view(image);
    vk_depth->clean_depth_resource(image);
    vk_framebuffer->clean_framebuffer(image);
    delete image;
  }

  vec_image.clear();

  //---------------------------
}
void VK_image::clean_image_view(Image* image){
  VkDevice device = vk_device->get_device();
  //---------------------------

  vkDestroyImageView(device, image->image_view, nullptr);

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
