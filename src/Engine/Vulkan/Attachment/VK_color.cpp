#include "VK_color.h"

#include "../Engine.h"
#include "../Param_vulkan.h"
#include "../Rendering/VK_framebuffer.h"
#include "../Attachment/VK_depth.h"
#include "../Data/VK_texture.h"
#include "../Device/VK_physical_device.h"


//Constructor / Destructor
VK_color::VK_color(Engine* engineManager){
  //---------------------------

  this->engineManager = engineManager;
  this->param_vulkan = engineManager->get_param_vulkan();
  this->vk_physical_device = engineManager->get_vk_physical_device();
  this->vk_texture = engineManager->get_vk_texture();

  //---------------------------
}
VK_color::~VK_color(){}

//Main function
void VK_color::create_color_attachment(Frame_swapchain* image){
  //---------------------------

  image->color.format = find_color_format();
  vk_texture->create_image(param_vulkan->window.extent.width, param_vulkan->window.extent.height, image->color.format, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT, MEMORY_GPU, image->color.image, image->color.mem);
  image->color.view = vk_texture->create_image_view(image->color.image, image->color.format, VK_IMAGE_ASPECT_COLOR_BIT);

  //---------------------------
}
void VK_color::clean_color_attachment(Frame_swapchain* image){
  //---------------------------

  vkDestroyImageView(param_vulkan->device.device, image->color.view, nullptr);
  vkDestroyImage(param_vulkan->device.device, image->color.image, nullptr);
  vkFreeMemory(param_vulkan->device.device, image->color.mem, nullptr);

  //---------------------------
}

//Subfunction
VkSurfaceFormatKHR VK_color::retrieve_surface_format(const std::vector<VkSurfaceFormatKHR>& dev_format){
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
VkFormat VK_color::find_color_format(){
  //---------------------------

  vector<VkSurfaceFormatKHR> surface_format = vk_physical_device->find_surface_format(param_vulkan->device.physical_device);
  VkSurfaceFormatKHR surfaceFormat = retrieve_surface_format(surface_format);
  VkFormat format = surfaceFormat.format;

  //---------------------------
  return format;
}
