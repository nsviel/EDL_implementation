#include "VK_image.h"

#include "../Engine.h"
#include "../Param_vulkan.h"
#include "../Command/VK_synchronization.h"
#include "../Rendering/VK_framebuffer.h"
#include "../Attachment/VK_depth.h"
#include "../Data/VK_texture.h"
#include "../Device/VK_physical_device.h"


//Constructor / Destructor
VK_image::VK_image(Engine* engineManager){
  //---------------------------

  this->engineManager = engineManager;
  this->param_vulkan = engineManager->get_param_vulkan();
  this->vk_physical_device = engineManager->get_vk_physical_device();
  this->vk_texture = engineManager->get_vk_texture();
  this->vk_synchronization = engineManager->get_vk_synchronization();

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
    image->color.image = vec_image_swapchain[i];
    this->create_image_view(image);
    vk_depth->create_depth_attachment(image);
    vec_image.push_back(image);
  }

  //Draw frames
  for(int i=0; i<param_vulkan->max_frame; i++){
    Frame* frame = new Frame();
    vk_synchronization->create_sync_objects(frame);
    vec_frame.push_back(frame);
  }

  //---------------------------
}
void VK_image::create_image_view(Image* image){
  //---------------------------

  image->color.format = find_color_format();

  //Image view settings & creation
  image->color.view = vk_texture->create_image_view(image->color.image, image->color.format, VK_IMAGE_ASPECT_COLOR_BIT);

  //---------------------------
}
void VK_image::create_image_swapchain(VkSwapchainKHR swapchain, unsigned int min_image_count){
  //---------------------------

  //Empty swapchain image
  vkGetSwapchainImagesKHR(param_vulkan->device, swapchain, &min_image_count, nullptr);

  //Fill swapchain image
  vec_image_swapchain.resize(min_image_count);
  vkGetSwapchainImagesKHR(param_vulkan->device, swapchain, &min_image_count, vec_image_swapchain.data());

  //---------------------------
}

//Deletio function
void VK_image::clean_image_struct(){
  VK_depth* vk_depth = engineManager->get_vk_depth();
  VK_framebuffer* vk_framebuffer = engineManager->get_vk_framebuffer();
  //---------------------------

  //Vec images
  for(int i=0; i<vec_image.size(); i++){
    Image* image = vec_image[i];
    this->clean_image_view(image);
    vk_depth->clean_depth_attachment(image);
    vk_framebuffer->clean_framebuffer(image);
    delete image;
  }
  vec_image.clear();

  //---------------------------
}
void VK_image::clean_frame_struct(){
  //---------------------------

  for(int i=0; i<vec_frame.size(); i++){
    Frame* frame = vec_frame[i];
    vk_synchronization->clean_sync_obj(frame);
    delete frame;
  }
  vec_frame.clear();

  //---------------------------
}
void VK_image::clean_image_view(Image* image){
  //---------------------------

  vkDestroyImageView(param_vulkan->device, image->color.view, nullptr);

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
VkFormat VK_image::find_color_format(){
  //---------------------------

  vector<VkSurfaceFormatKHR> surface_format = vk_physical_device->find_surface_format(param_vulkan->physical_device);
  VkSurfaceFormatKHR surfaceFormat = retrieve_surface_format(surface_format);
  VkFormat format = surfaceFormat.format;

  //---------------------------
  return format;
}
