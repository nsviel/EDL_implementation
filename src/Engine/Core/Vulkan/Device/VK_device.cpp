#include "VK_device.h"
#include "VK_physical_device.h"

#include "../VK_engine.h"
#include "../VK_param.h"


//Constructor / Destructor
VK_device::VK_device(VK_engine* vk_engine){
  //---------------------------

  this->vk_param = vk_engine->get_vk_param();
  this->vk_physical_device = vk_engine->get_vk_physical_device();

  //---------------------------
}
VK_device::~VK_device(){}

//Main functions
void VK_device::create_logical_device(){
  //Interface between selected GPU and application
  //---------------------------

  //Get GPU queue families
  int family_graphics = vk_physical_device->find_queue_family_graphics(vk_param->device.physical_device);
  int family_presentation = vk_physical_device->find_queue_family_presentation(vk_param->device.physical_device);
  std::set<uint32_t> uniqueQueueFamilies = {(unsigned int)family_graphics, (unsigned int)family_presentation};

  //Create queue on device
  float queuePriority = 1.0f;
  std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
  for(uint32_t queueFamily : uniqueQueueFamilies){
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
  createInfo.enabledExtensionCount = static_cast<uint32_t>(vk_param->device.extension.size());
  createInfo.ppEnabledExtensionNames = vk_param->device.extension.data();
  createInfo.enabledLayerCount = 0;

  //Creating the logical device
  VkResult result = vkCreateDevice(vk_param->device.physical_device, &createInfo, nullptr, &vk_param->device.device);
  if(result != VK_SUCCESS){
    throw std::runtime_error("failed to create logical device!");
  }

  //Get queue family handles
  vkGetDeviceQueue(vk_param->device.device, family_graphics, 0, &vk_param->device.queue_graphics);
  vkGetDeviceQueue(vk_param->device.device, family_presentation, 0, &vk_param->device.queue_presentation);

  //---------------------------
}
void VK_device::clean_logical_device(){
  //---------------------------

  vkDestroyDevice(vk_param->device.device, nullptr);

  //---------------------------
}
