#include "VK_depth.h"

#include "../Swapchain/VK_swapchain.h"
#include "../Device/VK_device.h"
#include "../Device/VK_physical_device.h"
#include "../Data/VK_texture.h"
#include "../Swapchain/VK_image.h"
#include "../Engine.h"


//Constructor / Destructor
VK_depth::VK_depth(Engine* engineManager){
  //---------------------------

  this->engineManager = engineManager;
  this->vk_device = engineManager->get_vk_device();
  this->vk_texture = engineManager->get_vk_texture();
  this->vk_swapchain = engineManager->get_vk_swapchain();
  this->vk_physical_device = engineManager->get_vk_physical_device();
  this->vk_image = engineManager->get_vk_image();

  //---------------------------
}
VK_depth::~VK_depth(){}

//Main function
void VK_depth::create_depth_resource(Image* image){
  vector<Image*> vec_image_obj = vk_image->get_vec_image();
  //---------------------------

  VkFormat depth_format = find_depth_format();
  VkExtent2D swapchain_extent = vk_swapchain->get_extent();

  vk_texture->create_image(swapchain_extent.width, swapchain_extent.height, depth_format, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, image->depth, image->depth_memory);
  image->depth_view = vk_texture->create_image_view(image->depth, depth_format, VK_IMAGE_ASPECT_DEPTH_BIT);

  //---------------------------
}
void VK_depth::clean_depth_resource(Image* image){
  VkDevice device = vk_device->get_device();
  //---------------------------

  vkDestroyImageView(device, image->depth_view, nullptr);
  vkDestroyImage(device, image->depth, nullptr);
  vkFreeMemory(device, image->depth_memory, nullptr);

  //---------------------------
}

//Subfunctions
bool VK_depth::find_stencil_component(VkFormat format){
  //---------------------------

  return format == VK_FORMAT_D32_SFLOAT_S8_UINT || format == VK_FORMAT_D24_UNORM_S8_UINT;

  //---------------------------
}
VkFormat VK_depth::find_supported_format(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features){
  VkPhysicalDevice physical_device = vk_physical_device->get_physical_device();
  //---------------------------

  for(VkFormat format : candidates){
    VkFormatProperties props;
    vkGetPhysicalDeviceFormatProperties(physical_device, format, &props);

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
