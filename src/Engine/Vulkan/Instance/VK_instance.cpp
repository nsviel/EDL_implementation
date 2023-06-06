#include "VK_instance.h"
#include "Element/VK_validation.h"

#include "../VK_engine.h"
#include "../VK_param.h"


//Constructor / Destructor
VK_instance::VK_instance(VK_engine* vk_engine){
  //---------------------------

  this->vk_engine = vk_engine;
  this->vk_param = vk_engine->get_vk_param();

  vk_param->instance.extension.push_back(VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME);

  //---------------------------
}
VK_instance::~VK_instance(){}

//Main function
void VK_instance::create_instance(){
  VK_validation* vk_validation = vk_engine->get_vk_validation();
  //---------------------------

  //Application info
  VkApplicationInfo appInfo{};
  appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  appInfo.pApplicationName = "Nephos";
  appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
  appInfo.pEngineName = "NoEngine";
  appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
  appInfo.apiVersion = VK_API_VERSION_1_0;

  //Instance info
  vector<const char*> validation_layers = vk_validation->get_validation_layers();
  VkInstanceCreateInfo createInfo{};
  createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  createInfo.pApplicationInfo = &appInfo;
  createInfo.enabledExtensionCount = static_cast<uint32_t>(vk_param->instance.extension.size());
  createInfo.ppEnabledExtensionNames = vk_param->instance.extension.data();
  createInfo.enabledLayerCount = static_cast<uint32_t>(validation_layers.size());
  createInfo.ppEnabledLayerNames = validation_layers.data();
  createInfo.pNext = vk_validation->find_validation_extension();

  //Create instance
  VkResult result = vkCreateInstance(&createInfo, nullptr, &vk_param->instance.instance);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to create instance!");
  }

  //---------------------------
}
void VK_instance::clean_instance(){
  //---------------------------

  vkDestroyInstance(vk_param->instance.instance, nullptr);

  //---------------------------
}
