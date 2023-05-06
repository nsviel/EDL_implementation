#include "VK_depth.h"
#include "VK_swapchain.h"

#include "../Device/VK_device.h"
#include "../Data/VK_texture.h"
#include "../Engine.h"


//Constructor / Destructor
VK_depth::VK_depth(Engine* engineManager){
  //---------------------------

  this->engineManager = engineManager;
  this->vk_device = engineManager->get_vk_device();
  this->vk_texture = engineManager->get_vk_texture();
  this->vk_swapchain = engineManager->get_vk_swapchain();

  //---------------------------
}
VK_depth::~VK_depth(){}

//Main function
void VK_depth::create_depth_resources(){
  VkExtent2D swapchain_extent = vk_swapchain->get_swapChain_extent();
  //---------------------------

  VkFormat depthFormat = findDepthFormat();

  vk_texture->create_image(swapchain_extent.width, swapchain_extent.height, depthFormat, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, depthImage, depthImageMemory);
  depthImageView = vk_texture->create_image_view(depthImage, depthFormat, VK_IMAGE_ASPECT_DEPTH_BIT);

  //---------------------------
}

//Subfunctions
VkFormat VK_depth::findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features){
  VkPhysicalDevice physical_device = vk_device->get_physical_device();
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
VkFormat VK_depth::findDepthFormat(){
  //---------------------------

  return findSupportedFormat(
    {VK_FORMAT_D32_SFLOAT, VK_FORMAT_D32_SFLOAT_S8_UINT, VK_FORMAT_D24_UNORM_S8_UINT},
    VK_IMAGE_TILING_OPTIMAL,
    VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT
  );

  //---------------------------
}
bool VK_depth::hasStencilComponent(VkFormat format){
  //---------------------------

  return format == VK_FORMAT_D32_SFLOAT_S8_UINT || format == VK_FORMAT_D24_UNORM_S8_UINT;

  //---------------------------
}
void VK_depth::cleanup(){
  VkDevice device = vk_device->get_device();
  //---------------------------

  vkDestroyImageView(device, depthImageView, nullptr);
  vkDestroyImage(device, depthImage, nullptr);
  vkFreeMemory(device, depthImageMemory, nullptr);

  //---------------------------
}
