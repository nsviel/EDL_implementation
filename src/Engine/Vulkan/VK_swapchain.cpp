#include "VK_swapchain.h"
#include "VK_device.h"
#include "VK_swapchain.h"
#include "VK_framebuffer.h"
#include "Engine_vulkan.h"

#include "../Core/Engine_window.h"

#include "../Node_engine.h"



//Constructor / Destructor
VK_swapchain::VK_swapchain(Engine_vulkan* engine_vulkan){
  //---------------------------

  this->engine_vulkan = engine_vulkan;
  this->engine_window = engine_vulkan->get_engine_window();
  this->vk_device = engine_vulkan->get_vk_device();


  //---------------------------
}
VK_swapchain::~VK_swapchain(){}

//Main function
void VK_swapchain::create_swapChain(){
  VkPhysicalDevice physical_device = engine_vulkan->get_physical_device();
  VkSurfaceKHR surface = engine_vulkan->get_vk_surface();
  VkDevice device = vk_device->get_device();
  //---------------------------

  //Get swap chain
  struct_swapChain_details swapChain_setting = find_swapChain_details(physical_device);

  //Retrieve settings
  VkSurfaceFormatKHR surfaceFormat = swapChain_surface_format(swapChain_setting.formats);
  VkPresentModeKHR presentation_mode = swapChain_presentation_mode(swapChain_setting.mode_presentation);
  VkExtent2D extent = swapChain_extent_setting(swapChain_setting.capabilities);

  //Get swap chain image capacity (0 means no maximum)
  uint32_t nb_image = swapChain_setting.capabilities.minImageCount + 1;
  if(swapChain_setting.capabilities.maxImageCount > 0 && nb_image > swapChain_setting.capabilities.maxImageCount){
    nb_image = swapChain_setting.capabilities.maxImageCount;
  }

  //Create swap chain info
  VkSwapchainCreateInfoKHR createInfo{};
  createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
  createInfo.surface = surface;
  createInfo.minImageCount = nb_image;
  createInfo.imageFormat = surfaceFormat.format;
  createInfo.imageColorSpace = surfaceFormat.colorSpace;
  createInfo.imageExtent = extent;
  createInfo.imageArrayLayers = 1;
  createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT; //VK_IMAGE_USAGE_TRANSFER_DST_BIT for post-processing

  //Link with queue families
  struct_queueFamily_indices indices = vk_device->find_queue_families(physical_device);
  uint32_t queueFamilyIndices[] = {indices.family_graphics.value(), indices.family_presentation.value()};

  if(indices.family_graphics != indices.family_presentation){
    createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
    createInfo.queueFamilyIndexCount = 2;
    createInfo.pQueueFamilyIndices = queueFamilyIndices;
  }else{
    createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
    createInfo.queueFamilyIndexCount = 0; // Optional
    createInfo.pQueueFamilyIndices = nullptr; // Optional
  }

  createInfo.preTransform = swapChain_setting.capabilities.currentTransform;
  createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR; //Ignore alpha channel
  createInfo.presentMode = presentation_mode;
  createInfo.clipped = VK_TRUE;
  createInfo.oldSwapchain = VK_NULL_HANDLE;

  //Create swap chain
  VkResult result = vkCreateSwapchainKHR(device, &createInfo, nullptr, &swapChain);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to create swap chain!");
  }

  //Swap chain handler
  vkGetSwapchainImagesKHR(device, swapChain, &nb_image, nullptr);
  swapChain_images.resize(nb_image);
  vkGetSwapchainImagesKHR(device, swapChain, &nb_image, swapChain_images.data());

  //Store values
  this->swapChain_image_format = surfaceFormat.format;
  this->swapChain_extent = extent;

  //---------------------------
}
void VK_swapchain::create_image_views(){
  VkDevice device = vk_device->get_device();
  //---------------------------

  //Resize the image view vector
  swapChain_image_views.resize(swapChain_images.size());

  //Image view settings & creation
  for (size_t i = 0; i < swapChain_images.size(); i++) {
    VkImageViewCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    createInfo.image = swapChain_images[i];
    createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
    createInfo.format = swapChain_image_format;
    createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
    createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
    createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
    createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
    createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    createInfo.subresourceRange.baseMipLevel = 0;
    createInfo.subresourceRange.levelCount = 1;
    createInfo.subresourceRange.baseArrayLayer = 0;
    createInfo.subresourceRange.layerCount = 1;

    VkResult result = vkCreateImageView(device, &createInfo, nullptr, &swapChain_image_views[i]);
    if(result != VK_SUCCESS){
      throw std::runtime_error("[error] failed to create image views!");
    }
  }

  //---------------------------
}

//Swap chain settings
struct_swapChain_details VK_swapchain::find_swapChain_details(VkPhysicalDevice device){
  struct_swapChain_details details;
  VkSurfaceKHR surface = engine_vulkan->get_vk_surface();
  //---------------------------

  //Get basic surface capabilities
  vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &details.capabilities);

  //Get supported surface format number
  uint32_t nb_format;
  vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &nb_format, nullptr);

  //Get supported surface format list
  if(nb_format != 0){
    details.formats.resize(nb_format);
    vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &nb_format, details.formats.data());
  }

  //Get presentation mode number
  uint32_t nb_mode_presentation;
  vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &nb_mode_presentation, nullptr);

  //Get presentation mode list
  if(nb_mode_presentation != 0){
    details.mode_presentation.resize(nb_mode_presentation);
    vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &nb_mode_presentation, details.mode_presentation.data());
  }

  //---------------------------
  return details;
}
VkSurfaceFormatKHR VK_swapchain::swapChain_surface_format(const std::vector<VkSurfaceFormatKHR>& availableFormats){
  //---------------------------

  //Check if standar RGB is available
  for(const auto& format : availableFormats){
    if(format.format == VK_FORMAT_B8G8R8A8_SRGB && format.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR){
      return format;
    }
  }

  //---------------------------
  return availableFormats[0];
}
VkPresentModeKHR VK_swapchain::swapChain_presentation_mode(const std::vector<VkPresentModeKHR>& availablePresentModes){
  //4 possible modes:
  //- VK_PRESENT_MODE_IMMEDIATE_KHR
  //- VK_PRESENT_MODE_FIFO_KHR
  //- VK_PRESENT_MODE_FIFO_RELAXED_KHR
  //- VK_PRESENT_MODE_MAILBOX_KHR
  //---------------------------

  //Check for VK_PRESENT_MODE_MAILBOX_KHR mode
  for(const auto& mode : availablePresentModes){
    if(mode == VK_PRESENT_MODE_MAILBOX_KHR){
      return mode;
    }
  }

  //---------------------------
  return VK_PRESENT_MODE_FIFO_KHR;
}
VkExtent2D VK_swapchain::swapChain_extent_setting(const VkSurfaceCapabilitiesKHR& capabilities){
  //Resolution of the swap chain image
  VkExtent2D extent;
  //---------------------------

  if(capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max()){
    extent = capabilities.currentExtent;
  }else{
    glm::vec2 fbo_dim = engine_window->get_framebuffer_size();

    extent = {
      static_cast<uint32_t>(fbo_dim.x),
      static_cast<uint32_t>(fbo_dim.y)
    };

    extent.width = std::clamp(extent.width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
    extent.height = std::clamp(extent.height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);
  }

  //---------------------------
  return extent;
}
void VK_swapchain::recreate_swapChain(){
  VkDevice device = vk_device->get_device();
  VK_framebuffer* vk_framebuffer = engine_vulkan->get_vk_framebuffer();
  //---------------------------

  vkDeviceWaitIdle(device);

  this->cleanup_swapChain();

  create_swapChain();
  create_image_views();
  vk_framebuffer->create_framebuffers();
  this->swapChain_fbo = vk_framebuffer->get_swapChain_fbo();

  //---------------------------
}
void VK_swapchain::cleanup_swapChain(){
  VkDevice device = vk_device->get_device();
  //---------------------------

  for(size_t i=0; i<swapChain_fbo.size(); i++){
    vkDestroyFramebuffer(device, swapChain_fbo[i], nullptr);
  }

  for(size_t i=0; i<swapChain_image_views.size(); i++){
    vkDestroyImageView(device, swapChain_image_views[i], nullptr);
  }

  vkDestroySwapchainKHR(device, swapChain, nullptr);

  //---------------------------
}
