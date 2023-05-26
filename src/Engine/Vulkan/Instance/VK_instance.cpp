#include "VK_instance.h"
#include "VK_validation.h"

#include "../Engine.h"
#include "../Param_vulkan.h"


//Constructor / Destructor
VK_instance::VK_instance(Engine* engineManager){
  //---------------------------

  this->engineManager = engineManager;
  this->param_vulkan = engineManager->get_param_vulkan();

  param_vulkan->instance.extension.push_back(VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME);

  //---------------------------
}
VK_instance::~VK_instance(){}

//Main function
void VK_instance::create_instance(){
  VK_validation* vk_validation = engineManager->get_vk_validation();
  //---------------------------

  //Application info
  VkApplicationInfo appInfo{};
  appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  appInfo.pApplicationName = "Hello Triangle";
  appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
  appInfo.pEngineName = "No Engine";
  appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
  appInfo.apiVersion = VK_API_VERSION_1_0;

  //Instance info
  vector<const char*> validation_layers = vk_validation->get_validation_layers();
  VkInstanceCreateInfo createInfo{};
  createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  createInfo.pApplicationInfo = &appInfo;
  createInfo.enabledExtensionCount = static_cast<uint32_t>(param_vulkan->instance.extension.size());
  createInfo.ppEnabledExtensionNames = param_vulkan->instance.extension.data();
  createInfo.enabledLayerCount = static_cast<uint32_t>(validation_layers.size());
  createInfo.ppEnabledLayerNames = validation_layers.data();
  createInfo.pNext = vk_validation->find_validation_extension();

  //Create instance
  VkResult result = vkCreateInstance(&createInfo, nullptr, &param_vulkan->instance.instance);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to create instance!");
  }

  //---------------------------
}
void VK_instance::cleanup(){
  //---------------------------

  vkDestroyInstance(param_vulkan->instance.instance, nullptr);

  //---------------------------
}
