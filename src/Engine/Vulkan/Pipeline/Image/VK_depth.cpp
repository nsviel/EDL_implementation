#include "VK_depth.h"

#include "../../VK_engine.h"
#include "../../VK_param.h"
#include "../Image/VK_image.h"


//Constructor / Destructor
VK_depth::VK_depth(VK_engine* vk_engine){
  //---------------------------

  this->vk_engine = vk_engine;
  this->vk_param = vk_engine->get_vk_param();
  this->vk_image = vk_engine->get_vk_image();

  //---------------------------
}
VK_depth::~VK_depth(){}

//Main function
void VK_depth::create_depth_attachment(Frame* frame){
  //---------------------------

  //Create frame depth image
  frame->depth.format = find_depth_format();
  frame->depth.width = vk_param->window.extent.width;
  frame->depth.height = vk_param->window.extent.height;
  frame->depth.tiling = VK_IMAGE_TILING_OPTIMAL;
  frame->depth.usage = frame->depth.usage;
  frame->depth.properties = MEMORY_GPU;
  frame->depth.aspect = VK_IMAGE_ASPECT_DEPTH_BIT;

  vk_image->create_image(&frame->depth);
  vk_image->create_image_view(&frame->depth);

  //---------------------------
}
void VK_depth::clean_depth_attachment(Frame* image){
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
