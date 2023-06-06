#include "VK_color.h"

#include "../Renderpass/VK_framebuffer.h"
#include "../Attachment/VK_depth.h"
#include "../Image/VK_texture.h"

#include "../../VK_engine.h"
#include "../../VK_param.h"
#include "../../Instance/Device/VK_physical_device.h"


//Constructor / Destructor
VK_color::VK_color(VK_engine* vk_engine){
  //---------------------------

  this->vk_engine = vk_engine;
  this->vk_param = vk_engine->get_vk_param();
  this->vk_physical_device = vk_engine->get_vk_physical_device();
  this->vk_texture = vk_engine->get_vk_texture();

  //---------------------------
}
VK_color::~VK_color(){}

//Main function
void VK_color::create_color_attachment(Frame* frame){
  //---------------------------

  //Create frame color image
  frame->color.format = find_color_format();
  frame->color.width = vk_param->window.extent.width;
  frame->color.height = vk_param->window.extent.height;
  frame->color.tiling = VK_IMAGE_TILING_OPTIMAL;
  frame->color.usage = IMAGE_USAGE_DEPTH;
  frame->color.properties = MEMORY_GPU;
  frame->color.aspect = VK_IMAGE_ASPECT_COLOR_BIT;

  vk_texture->create_image(&frame->color);
  vk_texture->create_image_view(&frame->color);

  //---------------------------
}
void VK_color::clean_color_attachment(Frame* image){
  //---------------------------

  vkDestroyImageView(vk_param->device.device, image->color.view, nullptr);
  vkDestroyImage(vk_param->device.device, image->color.image, nullptr);
  vkFreeMemory(vk_param->device.device, image->color.mem, nullptr);

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

  vector<VkSurfaceFormatKHR> surface_format = vk_physical_device->find_surface_format(vk_param->device.physical_device);
  VkSurfaceFormatKHR surfaceFormat = retrieve_surface_format(surface_format);
  VkFormat format = surfaceFormat.format;

  //---------------------------
  return format;
}
