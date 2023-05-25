#include "VK_swapchain.h"
#include "VK_image.h"

#include "../Engine.h"
#include "../Param_vulkan.h"
#include "../Rendering/VK_framebuffer.h"
#include "../Attachment/VK_depth.h"
#include "../Data/VK_texture.h"
#include "../Device/VK_device.h"
#include "../Device/VK_physical_device.h"
#include "../Instance/VK_window.h"


//Constructor / Destructor
VK_swapchain::VK_swapchain(Engine* engineManager){
  //---------------------------

  this->engineManager = engineManager;
  this->param_vulkan = engineManager->get_param_vulkan();
  this->vk_window = engineManager->get_vk_window();
  this->vk_device = engineManager->get_vk_device();
  this->vk_physical_device = engineManager->get_vk_physical_device();

  //---------------------------
}
VK_swapchain::~VK_swapchain(){}

//Swap chain creation
void VK_swapchain::create_swapchain(){
  //---------------------------

  //Create swap chain info
  VkSwapchainCreateInfoKHR createInfo{};
  this->create_swapchain_surface(createInfo);
  this->create_swapchain_family(createInfo);
  this->create_swapchain_presentation(createInfo);

  //Create swap chain
  VkResult result = vkCreateSwapchainKHR(param_vulkan->device, &createInfo, nullptr, &swapchain);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to create swap chain!");
  }

  this->swapchain_image(swapchain, createInfo.minImageCount);

  //---------------------------
}
void VK_swapchain::create_swapchain_surface(VkSwapchainCreateInfoKHR& createInfo){
  VkSurfaceKHR surface = vk_window->get_surface();
  //---------------------------

  VkSurfaceCapabilitiesKHR surface_capability = vk_physical_device->find_surface_capability(param_vulkan->physical_device);
  vector<VkSurfaceFormatKHR> surface_format = vk_physical_device->find_surface_format(param_vulkan->physical_device);
  VkSurfaceFormatKHR surfaceFormat = swapchain_surface_format(surface_format);

  //Get swap chain image capacity (0 means no maximum)
  uint32_t nb_image = surface_capability.minImageCount + 1;
  if(surface_capability.maxImageCount > 0 && nb_image > surface_capability.maxImageCount){
    nb_image = surface_capability.maxImageCount;
  }

  createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
  createInfo.minImageCount = nb_image;
  createInfo.surface = surface;
  createInfo.imageFormat = surfaceFormat.format;
  createInfo.imageColorSpace = surfaceFormat.colorSpace;
  createInfo.imageExtent = param_vulkan->extent;
  createInfo.imageArrayLayers = 1;
  createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT; //VK_IMAGE_USAGE_TRANSFER_DST_BIT for post-processing

  createInfo.preTransform = surface_capability.currentTransform;



  //---------------------------
}
void VK_swapchain::create_swapchain_family(VkSwapchainCreateInfoKHR& createInfo){
  //---------------------------

  //Link with queue families
  int family_graphics = vk_physical_device->find_queue_family_graphics(param_vulkan->physical_device);
  int family_presentation = vk_physical_device->find_queue_family_presentation(param_vulkan->physical_device);
  uint32_t queueFamilyIndices[] = {(unsigned int)family_graphics, (unsigned int)family_presentation};

  if(family_graphics != family_presentation){
    createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
    createInfo.queueFamilyIndexCount = 2;
    createInfo.pQueueFamilyIndices = queueFamilyIndices;
  }else{
    createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
    createInfo.queueFamilyIndexCount = 0; // Optional
    createInfo.pQueueFamilyIndices = nullptr; // Optional
  }

  //---------------------------
}
void VK_swapchain::create_swapchain_presentation(VkSwapchainCreateInfoKHR& createInfo){
  //---------------------------

  vector<VkPresentModeKHR> dev_presentation_mode = vk_physical_device->find_presentation_mode(param_vulkan->physical_device);
  VkPresentModeKHR presentation_mode = swapchain_presentation_mode(dev_presentation_mode);

  createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR; //Ignore alpha channel
  createInfo.presentMode = presentation_mode;
  createInfo.clipped = VK_TRUE;
  createInfo.oldSwapchain = VK_NULL_HANDLE;

  //---------------------------
}

//Swap chain function
void VK_swapchain::recreate_swapChain(){
  VK_depth* vk_depth = engineManager->get_vk_depth();
  VK_image* vk_image = engineManager->get_vk_image();
  VK_framebuffer* vk_framebuffer = engineManager->get_vk_framebuffer();
  GLFWwindow* window = vk_window->get_window();
  //---------------------------

  //Minimization managment
  int width = 0, height = 0;
  while(width == 0 || height == 0){
    glfwGetFramebufferSize(window, &width, &height);
    glfwWaitEvents();
  }

  vkDeviceWaitIdle(param_vulkan->device);

  //Clean old values
  vk_image->clean_image_struct();
  this->clean_swapchain();

  //Recreate values
  vk_physical_device->compute_extent();
  this->create_swapchain();
  vk_image->create_image_struct();
  vk_framebuffer->create_framebuffer_obj();

  //---------------------------
}
void VK_swapchain::clean_swapchain(){
  //---------------------------

  vkDestroySwapchainKHR(param_vulkan->device, swapchain, nullptr);

  //---------------------------
}

//Swap chain parameter
void VK_swapchain::swapchain_image(VkSwapchainKHR swapchain, unsigned int min_image_count){
  //---------------------------

  //For swapchain image we use vkGetSwapchainImagesKHR instead of VkImageCreateInfo
  //to get the correct image which are managed by the presentation engine

  //Empty swapchain image
  vkGetSwapchainImagesKHR(param_vulkan->device, swapchain, &min_image_count, nullptr);

  //Fill swapchain image
  vec_swapchain_image.resize(min_image_count);
  vkGetSwapchainImagesKHR(param_vulkan->device, swapchain, &min_image_count, vec_swapchain_image.data());

  //---------------------------
}
VkSurfaceFormatKHR VK_swapchain::swapchain_surface_format(const std::vector<VkSurfaceFormatKHR>& dev_format){
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
VkPresentModeKHR VK_swapchain::swapchain_presentation_mode(const std::vector<VkPresentModeKHR>& dev_mode){
  //4 possible modes:
  //- VK_PRESENT_MODE_IMMEDIATE_KHR
  //- VK_PRESENT_MODE_FIFO_KHR
  //- VK_PRESENT_MODE_FIFO_RELAXED_KHR
  //- VK_PRESENT_MODE_MAILBOX_KHR
  //---------------------------

  //Check for VK_PRESENT_MODE_MAILBOX_KHR mode
  for(const auto& mode : dev_mode){
    if(mode == VK_PRESENT_MODE_MAILBOX_KHR){
      return mode;
    }
  }

  //---------------------------
  return VK_PRESENT_MODE_FIFO_KHR;
}
