#include "VK_device.h"

#include "../Engine.h"
#include "../Instance/VK_window.h"
#include "../Instance/VK_instance.h"

#include "../../Node_engine.h"



//Constructor / Destructor
VK_device::VK_device(Engine* engineManager){
  //---------------------------

  this->vk_window = engineManager->get_vk_window();
  this->vk_instance = engineManager->get_vk_instance();
  this->engineManager = engineManager;

  //---------------------------
}
VK_device::~VK_device(){}

//Main functions
void VK_device::init_device(){
  //---------------------------

  this->select_physical_device();
  this->create_logical_device();

  //---------------------------
}
void VK_device::select_physical_device(){
  VkInstance instance = vk_instance->get_instance();
  //---------------------------

  this->physical_device = VK_NULL_HANDLE;

  //Find how many GPU are available
  uint32_t nb_device = 0;
  vkEnumeratePhysicalDevices(instance, &nb_device, nullptr);
  if (nb_device == 0) {
    throw std::runtime_error("failed to find GPUs with Vulkan support!");
  }

  //List all available GPU and take suitable one
  std::vector<VkPhysicalDevice> devices(nb_device);
  vkEnumeratePhysicalDevices(instance, &nb_device, devices.data());
  for(const auto& device : devices){
    if(is_device_suitable(device)){
      physical_device = device;
      break;
    }
  }
  if(physical_device == VK_NULL_HANDLE){
    throw std::runtime_error("failed to find a suitable GPU!");
  }

  //---------------------------
}
void VK_device::create_logical_device(){
  //Interface between selected GPU and application
  //---------------------------

  //Get GPU qeue families
  struct_queueFamily_indices indices = find_queue_families(physical_device);

  std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
  std::set<uint32_t> uniqueQueueFamilies = {
    indices.family_graphics.value(),
    indices.family_presentation.value()
  };

  float queuePriority = 1.0f;
  for (uint32_t queueFamily : uniqueQueueFamilies) {
    VkDeviceQueueCreateInfo queueCreateInfo{};
    queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queueCreateInfo.queueFamilyIndex = queueFamily;
    queueCreateInfo.queueCount = 1;
    queueCreateInfo.pQueuePriorities = &queuePriority;
    queueCreateInfos.push_back(queueCreateInfo);
  }

  //Specifying used device features
  VkPhysicalDeviceFeatures deviceFeatures{};
  deviceFeatures.samplerAnisotropy = VK_TRUE;
  deviceFeatures.wideLines = VK_TRUE;

  //Logical device info
  VkDeviceCreateInfo createInfo{};
  createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
  createInfo.pQueueCreateInfos = queueCreateInfos.data();
  createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
  createInfo.pEnabledFeatures = &deviceFeatures;
  createInfo.enabledExtensionCount = static_cast<uint32_t>(required_extensions.size());
  createInfo.ppEnabledExtensionNames = required_extensions.data();
  createInfo.enabledLayerCount = 0;

  //Creating the logical device
  VkResult result = vkCreateDevice(physical_device, &createInfo, nullptr, &device);
  if(result != VK_SUCCESS){
    throw std::runtime_error("failed to create logical device!");
  }

  //Get queue family handles
  vkGetDeviceQueue(device, indices.family_graphics.value(), 0, &queue_graphics);
  vkGetDeviceQueue(device, indices.family_presentation.value(), 0, &queue_presentation);

  //---------------------------
}
void VK_device::cleanup(){
  //---------------------------

  vkDestroyDevice(device, nullptr);

  //---------------------------
}

//Subfunctions
bool VK_device::is_device_suitable(VkPhysicalDevice device){
  //---------------------------

  //Queue suitable
  struct_queueFamily_indices queue_indices = find_queue_families(device);
  bool queue_ok = queue_indices.is_complete();

  //Extension suitable
  bool extension_ok = check_extension_support(device);

  //Swap chain suitable
  bool swapChain_ok = false;
  if(extension_ok){
    struct_swapChain_details swapChain_setting = find_swapChain_details(device);
    swapChain_ok = !swapChain_setting.formats.empty() && !swapChain_setting.mode_presentation.empty();
  }

  //Supported features
  VkPhysicalDeviceFeatures supportedFeatures;
  vkGetPhysicalDeviceFeatures(device, &supportedFeatures);
  bool msaa_ok = supportedFeatures.samplerAnisotropy;
  bool line_ok = supportedFeatures.wideLines;

  //---------------------------
  return queue_ok && extension_ok && swapChain_ok && msaa_ok && line_ok;
}
bool VK_device::check_extension_support(VkPhysicalDevice device){
  //---------------------------

  //Get device extension number
  uint32_t nb_extension;
  vkEnumerateDeviceExtensionProperties(device, nullptr, &nb_extension, nullptr);

  //List device extension
  std::vector<VkExtensionProperties> vec_extension(nb_extension);
  vkEnumerateDeviceExtensionProperties(device, nullptr, &nb_extension, vec_extension.data());

  //Check if all required extension are in the list
  std::set<std::string> requiredExtensions(required_extensions.begin(), required_extensions.end());
  for (const auto& extension : vec_extension) {
    requiredExtensions.erase(extension.extensionName);
  }

  //---------------------------
  return requiredExtensions.empty();
}

//Specific info retrieval
struct_queueFamily_indices VK_device::find_queue_families(VkPhysicalDevice device){
  struct_queueFamily_indices indices;
  VkSurfaceKHR surface = vk_window->get_surface();
  //---------------------------

  //Get queue family number
  uint32_t nb_queueFamily = 0;
  vkGetPhysicalDeviceQueueFamilyProperties(device, &nb_queueFamily, nullptr);
  if(nb_queueFamily == 0) {
    throw std::runtime_error("[error] No queue families on selected GPU");
  }

  //List queue families
  std::vector<VkQueueFamilyProperties> vec_queueFamily(nb_queueFamily);
  vkGetPhysicalDeviceQueueFamilyProperties(device, &nb_queueFamily, vec_queueFamily.data());

  //Search for specific properties (e.g, graphics)
  int i = 0;
  for(const auto& queueFamily : vec_queueFamily) {
    //Querying for graphics family
    if(queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
      indices.family_graphics = i;
    }

    //Querying for presentation family
    VkBool32 presentSupport = false;
    vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &presentSupport);
    if(presentSupport){
      indices.family_presentation = i;
    }

    //Break if complete
    if(indices.is_complete()){
      break;
    }

    i++;
  }

  //---------------------------
  return indices;
}
struct_swapChain_details VK_device::find_swapChain_details(VkPhysicalDevice device){
  struct_swapChain_details details;
  VkSurfaceKHR surface = vk_window->get_surface();
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
