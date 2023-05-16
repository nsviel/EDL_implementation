#include "VK_swapchain.h"
#include "VK_image.h"

#include "../Rendering/VK_framebuffer.h"
#include "../Rendering/VK_depth.h"
#include "../Data/VK_texture.h"
#include "../Device/VK_device.h"
#include "../Device/VK_physical_device.h"
#include "../Instance/VK_window.h"
#include "../Engine.h"


//Constructor / Destructor
VK_swapchain::VK_swapchain(Engine* engineManager){
  //---------------------------

  this->engineManager = engineManager;
  this->vk_window = engineManager->get_vk_window();
  this->vk_device = engineManager->get_vk_device();
  this->vk_physical_device = engineManager->get_vk_physical_device();
  this->vk_image = engineManager->get_vk_image();

  //---------------------------
}
VK_swapchain::~VK_swapchain(){}

//Swap chain creation
void VK_swapchain::create_swapchain(){
  VkDevice device = vk_device->get_device();
  //---------------------------

  //Create swap chain info
  VkSwapchainCreateInfoKHR createInfo{};
  this->create_swapchain_surface(createInfo);
  this->create_swapchain_family(createInfo);
  this->create_swapchain_presentation(createInfo);

  //Create swap chain
  VkResult result = vkCreateSwapchainKHR(device, &createInfo, nullptr, &swapchain);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to create swap chain!");
  }

  vk_image->create_image_swapchain(swapchain, createInfo.minImageCount);

  //---------------------------
}
void VK_swapchain::create_swapchain_surface(VkSwapchainCreateInfoKHR& createInfo){
  VkPhysicalDevice physical_device = vk_physical_device->get_physical_device();
  VkSurfaceKHR surface = vk_window->get_surface();
  //---------------------------

  VkSurfaceCapabilitiesKHR surface_capability = vk_physical_device->find_surface_capability(physical_device);
  vector<VkSurfaceFormatKHR> surface_format = vk_physical_device->find_surface_format(physical_device);
  VkSurfaceFormatKHR surfaceFormat = swapchain_surface_format(surface_format);
  this->compute_extent(surface_capability);

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
  createInfo.imageExtent = swapchain_extent;
  createInfo.imageArrayLayers = 1;
  createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT; //VK_IMAGE_USAGE_TRANSFER_DST_BIT for post-processing

  createInfo.preTransform = surface_capability.currentTransform;



  //---------------------------
}
void VK_swapchain::create_swapchain_family(VkSwapchainCreateInfoKHR& createInfo){
  VkPhysicalDevice physical_device = vk_physical_device->get_physical_device();
  //---------------------------

  //Link with queue families
  int family_graphics = vk_physical_device->find_queue_family_graphics(physical_device);
  int family_presentation = vk_physical_device->find_queue_family_presentation(physical_device);
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
  VkPhysicalDevice physical_device = vk_physical_device->get_physical_device();
  //---------------------------

  vector<VkPresentModeKHR> dev_presentation_mode = vk_physical_device->find_presentation_mode(physical_device);
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
  VkDevice device = vk_device->get_device();
  VK_framebuffer* vk_framebuffer = engineManager->get_vk_framebuffer();
  GLFWwindow* window = vk_window->get_window();
  //---------------------------

  //Minimization managment
  int width = 0, height = 0;
  while(width == 0 || height == 0){
    glfwGetFramebufferSize(window, &width, &height);
    glfwWaitEvents();
  }

  vkDeviceWaitIdle(device);

  //Clean old values
  vk_depth->cleanup();
  vk_framebuffer->cleanup();
  vk_image->cleanup();
  this->cleanup();

  //Recreate values
  this->create_swapchain();
  vk_image->create_image_views();
  vk_depth->create_depth_resources();
  vk_framebuffer->create_framebuffers();

  //---------------------------
}
void VK_swapchain::cleanup(){
  VkDevice device = vk_device->get_device();
  //---------------------------

  vkDestroySwapchainKHR(device, swapchain, nullptr);

  //---------------------------
}

//Swap chain parameter
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
void VK_swapchain::compute_extent(const VkSurfaceCapabilitiesKHR& capabilities){
  //Resolution of the swap chain image
  //---------------------------

  if(capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max()){
    swapchain_extent = capabilities.currentExtent;
  }else{
    glm::vec2 fbo_dim = vk_window->get_framebuffer_size();

    swapchain_extent = {
      static_cast<uint32_t>(fbo_dim.x),
      static_cast<uint32_t>(fbo_dim.y)
    };

    swapchain_extent.width = std::clamp(swapchain_extent.width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
    swapchain_extent.height = std::clamp(swapchain_extent.height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);
  }

  //---------------------------
}
