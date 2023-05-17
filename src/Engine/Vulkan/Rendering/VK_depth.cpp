#include "VK_depth.h"

#include "../Engine.h"
#include "../Param_vulkan.h"
#include "../Swapchain/VK_swapchain.h"
#include "../Device/VK_device.h"
#include "../Device/VK_physical_device.h"
#include "../Data/VK_texture.h"


//Constructor / Destructor
VK_depth::VK_depth(Engine* engineManager){
  //---------------------------

  this->engineManager = engineManager;
  this->param_vulkan = engineManager->get_param_vulkan();
  this->vk_device = engineManager->get_vk_device();
  this->vk_texture = engineManager->get_vk_texture();
  this->vk_swapchain = engineManager->get_vk_swapchain();
  this->vk_physical_device = engineManager->get_vk_physical_device();

  //---------------------------
}
VK_depth::~VK_depth(){}

//Main function
void VK_depth::create_depth_resource(Image* image){
  //---------------------------

  VkFormat depth_format = find_depth_format();

  vk_texture->create_image(param_vulkan->extent.width, param_vulkan->extent.height, depth_format, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, image->depth, image->depth_memory);
  image->depth_view = vk_texture->create_image_view(image->depth, depth_format, VK_IMAGE_ASPECT_DEPTH_BIT);

  //---------------------------
}
void VK_depth::clean_depth_resource(Image* image){
  //---------------------------

  vkDestroyImageView(param_vulkan->device, image->depth_view, nullptr);
  vkDestroyImage(param_vulkan->device, image->depth, nullptr);
  vkFreeMemory(param_vulkan->device, image->depth_memory, nullptr);

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
    vkGetPhysicalDeviceFormatProperties(param_vulkan->physical_device, format, &props);

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
