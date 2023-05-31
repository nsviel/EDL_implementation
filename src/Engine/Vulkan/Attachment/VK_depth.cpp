#include "VK_depth.h"

#include "../VK_engine.h"
#include "../VK_param.h"
#include "../Data/VK_texture.h"


//Constructor / Destructor
VK_depth::VK_depth(VK_engine* vk_engine){
  //---------------------------

  this->vk_engine = vk_engine;
  this->vk_param = vk_engine->get_vk_param();
  this->vk_texture = vk_engine->get_vk_texture();

  //---------------------------
}
VK_depth::~VK_depth(){}

//Main function
void VK_depth::create_depth_attachment(Frame_swapchain* image){
  //---------------------------

  image->depth.format = find_depth_format();
  vk_texture->create_image(vk_param->window.extent.width, vk_param->window.extent.height, image->depth.format, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT, MEMORY_GPU, image->depth.image, image->depth.mem);
  image->depth.view = vk_texture->create_image_view(image->depth.image, image->depth.format, VK_IMAGE_ASPECT_DEPTH_BIT);

  //---------------------------
}
void VK_depth::clean_depth_attachment(Frame_swapchain* image){
  //---------------------------

  vkDestroyImageView(vk_param->device.device, image->depth.view, nullptr);
  vkDestroyImage(vk_param->device.device, image->depth.image, nullptr);
  vkFreeMemory(vk_param->device.device, image->depth.mem, nullptr);

  //---------------------------
}

//Subfunctions
bool VK_depth::find_stencil_component(VkFormat format){
  //---------------------------

  return format == VK_FORMAT_D32_SFLOAT_S8_UINT || format == VK_FORMAT_D24_UNORM_S8_UINT;

  //---------------------------
}
VkFormat VK_depth::find_supported_format(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features){
  //---------------------------

  for(VkFormat format : candidates){
    VkFormatProperties props;
    vkGetPhysicalDeviceFormatProperties(vk_param->device.physical_device, format, &props);

    if(tiling == VK_IMAGE_TILING_LINEAR && (props.linearTilingFeatures & features) == features){
      return format;
    }else if(tiling == VK_IMAGE_TILING_OPTIMAL && (props.optimalTilingFeatures & features) == features){
      return format;
    }
  }

  throw std::runtime_error("[error] failed to find supported format!");

  //---------------------------
}
VkFormat VK_depth::find_depth_format(){
  //---------------------------

  return find_supported_format(
    {VK_FORMAT_D32_SFLOAT, VK_FORMAT_D32_SFLOAT_S8_UINT, VK_FORMAT_D24_UNORM_S8_UINT},
    VK_IMAGE_TILING_OPTIMAL,
    VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT
  );

  //---------------------------
}
