#include "VK_color.h"
#include "VK_depth.h"
#include "VK_image.h"

#include "../../VK_engine.h"
#include "../../VK_param.h"
#include "../../Instance/Device/VK_physical_device.h"
#include "../../Presentation/Swapchain/VK_framebuffer.h"


//Constructor / Destructor
VK_color::VK_color(VK_engine* vk_engine){
  //---------------------------

  this->vk_engine = vk_engine;
  this->vk_param = vk_engine->get_vk_param();
  this->vk_physical_device = vk_engine->get_vk_physical_device();
  this->vk_image = vk_engine->get_vk_image();

  //---------------------------
}
VK_color::~VK_color(){}

//Main function
void VK_color::create_color_attachment(Frame* frame){
  //---------------------------

  //Create frame color image
  frame->color.name = "tex_color";
  frame->color.format = find_color_format();
  frame->color.width = vk_param->window.extent.width;
  frame->color.height = vk_param->window.extent.height;
  frame->color.tiling = VK_IMAGE_TILING_OPTIMAL;
  frame->color.properties = MEMORY_GPU;
  frame->color.aspect = VK_IMAGE_ASPECT_COLOR_BIT;

  vk_image->create_image(&frame->color);
  vk_image->create_image_view(&frame->color);
  vk_image->create_image_sampler(&frame->color);

  //---------------------------
}

//Subfunction
VkSurfaceFormatKHR VK_color::retrieve_surface_format(const std::vector<VkSurfaceFormatKHR>& dev_format){
  //---------------------------

  //Check if standar RGB is available
  for(const auto& format : dev_format){
    if(format.format == vk_param->required_image_format && format.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR){
      return format;
    }
  }

  cout<<"[error] Standar RGB is no available"<<endl;

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
