#include "VK_device.h"
#include "VK_physical_device.h"

#include "../Engine.h"
#include "../Instance/VK_window.h"
#include "../Instance/VK_instance.h"

#include "../../Node_engine.h"



//Constructor / Destructor
VK_device::VK_device(Engine* engineManager){
  //---------------------------

  this->engineManager = engineManager;
  this->vk_window = engineManager->get_vk_window();
  this->vk_instance = engineManager->get_vk_instance();
  this->vk_physical_device = engineManager->get_vk_physical_device();

  //---------------------------
}
VK_device::~VK_device(){}

//Main functions
void VK_device::create_logical_device(){
  //Interface between selected GPU and application
  VkPhysicalDevice physical_device = vk_physical_device->get_physical_device();
  //---------------------------

  //Get GPU qeue families
  struct_queueFamily_indices indices = vk_physical_device->find_queue_families(physical_device);

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
