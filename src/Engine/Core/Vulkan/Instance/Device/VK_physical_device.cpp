#include "VK_physical_device.h"

#include "../Instance/VK_instance.h"
#include "../Element/VK_window.h"

#include "../../VK_engine.h"
#include "../../VK_param.h"


//Constructor / Destructor
VK_physical_device::VK_physical_device(VK_engine* vk_engine){
  //---------------------------

  this->vk_engine = vk_engine;
  this->vk_param = vk_engine->get_vk_param();
  this->vk_window = vk_engine->get_vk_window();
  this->vk_instance = vk_engine->get_vk_instance();

  vk_param->device.extension.push_back(VK_KHR_SWAPCHAIN_EXTENSION_NAME);
  vk_param->device.extension.push_back(VK_KHR_PUSH_DESCRIPTOR_EXTENSION_NAME);

  //---------------------------
}
VK_physical_device::~VK_physical_device(){}

//Main functions
void VK_physical_device::init_physical_device(){
  //---------------------------

  this->select_physical_device();
  this->compute_extent();
  this->retrieve_device_name();

  //---------------------------
}
void VK_physical_device::select_physical_device(){
  //---------------------------

  vk_param->device.physical_device = VK_NULL_HANDLE;

  //Find how many GPU are available
  uint32_t nb_device = 0;
  vkEnumeratePhysicalDevices(vk_param->instance.instance, &nb_device, nullptr);
  if(nb_device == 0){
    throw std::runtime_error("[error] failed to find GPUs with Vulkan support!");
  }

  //List all available GPU and take suitable one
  std::vector<VkPhysicalDevice> vec_physical_device(nb_device);
  vkEnumeratePhysicalDevices(vk_param->instance.instance, &nb_device, vec_physical_device.data());
  for(const auto& physical_device : vec_physical_device){
    if(is_device_suitable(physical_device)){
      vk_param->device.physical_device = physical_device;
      break;
    }
  }
  if(vk_param->device.physical_device == VK_NULL_HANDLE){
    throw std::runtime_error("[error] failed to find a suitable GPU!");
  }

  //---------------------------
}
void VK_physical_device::compute_extent(){
  //Resolution of the swap chain image
  //---------------------------

  VkSurfaceCapabilitiesKHR capabilities = find_surface_capability(vk_param->device.physical_device);

  if(capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max()){
    vk_param->window.extent = capabilities.currentExtent;
  }else{
    glm::vec2 fbo_dim = vk_window->get_framebuffer_size();

    vk_param->window.extent = {
      static_cast<uint32_t>(fbo_dim.x),
      static_cast<uint32_t>(fbo_dim.y)
    };

    vk_param->window.extent.width = std::clamp(vk_param->window.extent.width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
    vk_param->window.extent.height = std::clamp(vk_param->window.extent.height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);
  }

  //---------------------------
}
void VK_physical_device::retrieve_device_name(){
  //---------------------------

  VkPhysicalDeviceProperties property = find_device_property(vk_param->device.physical_device);
  vk_param->device.model = property.deviceName;
  
  //---------------------------
}

//Subfunctions
bool VK_physical_device::is_device_suitable(VkPhysicalDevice physical_device){
  //---------------------------

  //Queue suitable
  int family_graphics = find_queue_family_graphics(physical_device);
  int family_presentation = find_queue_family_presentation(physical_device);
  if(family_graphics == -1 || family_presentation == -1){
    return false;
  }

  //Extension suitable
  bool extension_ok = check_extension_support(physical_device);
  if(extension_ok == false){
    return false;
  }

  //Swap chain suitable
  vector<VkSurfaceFormatKHR> surface_format = find_surface_format(physical_device);
  vector<VkPresentModeKHR> presentation_mode = find_presentation_mode(physical_device);
  bool swapChain_ok = !surface_format.empty() && !presentation_mode.empty();
  if(swapChain_ok == false){
    return false;
  }

  //Supported features
  VkPhysicalDeviceFeatures supportedFeatures;
  vkGetPhysicalDeviceFeatures(physical_device, &supportedFeatures);
  bool msaa_ok = supportedFeatures.samplerAnisotropy;
  bool line_ok = supportedFeatures.wideLines;
  if(msaa_ok == false || line_ok == false){
    return false;
  }

  //---------------------------
  return true;
}
bool VK_physical_device::check_extension_support(VkPhysicalDevice physical_device){
  //---------------------------

  //Get physical_device extension number
  uint32_t nb_extension;
  vkEnumerateDeviceExtensionProperties(physical_device, nullptr, &nb_extension, nullptr);

  //List physical_device extension
  std::vector<VkExtensionProperties> vec_extension(nb_extension);
  vkEnumerateDeviceExtensionProperties(physical_device, nullptr, &nb_extension, vec_extension.data());

  //Check if all required extension are in the list
  std::set<std::string> requiredExtensions(vk_param->device.extension.begin(), vk_param->device.extension.end());
  for(const auto& extension : vec_extension){
    requiredExtensions.erase(extension.extensionName);
  }

  //---------------------------
  return requiredExtensions.empty();
}

//Specific info retrieval
int VK_physical_device::find_queue_family_graphics(VkPhysicalDevice physical_device){
  VkSurfaceKHR surface = vk_window->get_surface();
  //---------------------------

  //Get queue family number
  uint32_t nb_queueFamily = 0;
  vkGetPhysicalDeviceQueueFamilyProperties(physical_device, &nb_queueFamily, nullptr);
  if(nb_queueFamily == 0) {
    throw std::runtime_error("[error] No queue families on selected GPU");
  }

  //List queue families
  std::vector<VkQueueFamilyProperties> vec_queueFamily(nb_queueFamily);
  vkGetPhysicalDeviceQueueFamilyProperties(physical_device, &nb_queueFamily, vec_queueFamily.data());

  //Search for specific properties (e.g, graphics)
  int i = 0;
  for(const auto& queueFamily : vec_queueFamily){
    //Querying for graphics family
    if(queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT){
      return i;
    }
    i++;
  }

  //---------------------------
  return -1;
}
int VK_physical_device::find_queue_family_presentation(VkPhysicalDevice physical_device){
  VkSurfaceKHR surface = vk_window->get_surface();
  //---------------------------

  //Get queue family number
  uint32_t nb_queueFamily = 0;
  vkGetPhysicalDeviceQueueFamilyProperties(physical_device, &nb_queueFamily, nullptr);
  if(nb_queueFamily == 0) {
    throw std::runtime_error("[error] No queue families on selected GPU");
  }

  //List queue families
  std::vector<VkQueueFamilyProperties> vec_queueFamily(nb_queueFamily);
  vkGetPhysicalDeviceQueueFamilyProperties(physical_device, &nb_queueFamily, vec_queueFamily.data());

  //Search for specific properties (e.g, graphics)
  int i = 0;
  for(const auto& queueFamily : vec_queueFamily) {
    //Querying for presentation family
    VkBool32 presentSupport = false;
    vkGetPhysicalDeviceSurfaceSupportKHR(physical_device, i, surface, &presentSupport);
    if(presentSupport){
      return i;
    }
    i++;
  }

  //---------------------------
  return -1;
}

VkSurfaceCapabilitiesKHR VK_physical_device::find_surface_capability(VkPhysicalDevice physical_device){
  VkSurfaceKHR surface = vk_window->get_surface();
  //---------------------------

  //Get basic surface capabilities
  VkSurfaceCapabilitiesKHR capabilities;
  vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physical_device, surface, &capabilities);

  //---------------------------
  return capabilities;
}
vector<VkSurfaceFormatKHR> VK_physical_device::find_surface_format(VkPhysicalDevice physical_device){
  vector<VkSurfaceFormatKHR> formats;
  VkSurfaceKHR surface = vk_window->get_surface();
  //---------------------------

  //Get supported surface format number
  uint32_t nb_format;
  vkGetPhysicalDeviceSurfaceFormatsKHR(physical_device, surface, &nb_format, nullptr);

  //Get supported surface format list
  if(nb_format != 0){
    formats.resize(nb_format);
    vkGetPhysicalDeviceSurfaceFormatsKHR(physical_device, surface, &nb_format, formats.data());
  }

  //---------------------------
  return formats;
}
vector<VkPresentModeKHR> VK_physical_device::find_presentation_mode(VkPhysicalDevice physical_device){
  vector<VkPresentModeKHR> presentation_mode;
  VkSurfaceKHR surface = vk_window->get_surface();
  //---------------------------

  //Get presentation mode number
  uint32_t nb_mode_presentation;
  vkGetPhysicalDeviceSurfacePresentModesKHR(physical_device, surface, &nb_mode_presentation, nullptr);

  //Get presentation mode list
  if(nb_mode_presentation != 0){
    presentation_mode.resize(nb_mode_presentation);
    vkGetPhysicalDeviceSurfacePresentModesKHR(physical_device, surface, &nb_mode_presentation, presentation_mode.data());
  }

  //---------------------------
  return presentation_mode;
}
VkPhysicalDeviceProperties VK_physical_device::find_device_property(VkPhysicalDevice physical_device){
  //---------------------------

  VkPhysicalDeviceProperties property{};
  vkGetPhysicalDeviceProperties(vk_param->device.physical_device, &property);

  //---------------------------
  return property;
}
