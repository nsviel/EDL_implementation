#include "VK_validation.h"
#include "VK_instance.h"

#include "../Engine.h"


//Constructor / Destructor
VK_validation::VK_validation(Engine* engineManager){
  //---------------------------

  this->vk_instance = engineManager->get_vk_instance();

  this->validation_layers = {"VK_LAYER_KHRONOS_validation"};
  this->with_validation_layer = true;

  //---------------------------
}
VK_validation::~VK_validation(){}

//Main function
void VK_validation::create_validationLayer(){
  VkInstance instance = vk_instance->get_instance();
  //---------------------------

  if(!with_validation_layer) return;

  VkDebugUtilsMessengerCreateInfoEXT createInfo{};
  populateDebugMessengerCreateInfo(createInfo);

  VkResult result = CreateDebugUtilsMessengerEXT(instance, &createInfo, nullptr, &debugMessenger);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to set up debug messenger!");
  }

  //---------------------------
}
bool VK_validation::check_validationLayer_support(){
  //---------------------------

  //Checks if all of the requested layers are available
  uint32_t layerCount;
  vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

  std::vector<VkLayerProperties> availableLayers(layerCount);
  vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

  //Check if all of the layers in validation_layers exist in the availableLayers list
  for(const char* layerName : validation_layers){
    bool layerFound = false;

    for(const auto& layerProperties : availableLayers){
      if(strcmp(layerName, layerProperties.layerName) == 0){
        layerFound = true;
        break;
      }
    }

    if(!layerFound){
      return false;
    }
  }

  //---------------------------
  return true;
}
void VK_validation::cleanup(){
  VkInstance instance = vk_instance->get_instance();
  //---------------------------

  if(with_validation_layer){
    DestroyDebugUtilsMessengerEXT(instance, debugMessenger, nullptr);
  }

  //---------------------------
}

//Subfunction
void VK_validation::populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo){
  //---------------------------

  createInfo = {};
  createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
  createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
  createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
  createInfo.pfnUserCallback = debugCallback;

  //---------------------------
}
VkResult VK_validation::CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger) {
  //---------------------------

  auto func = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
  if (func != nullptr) {
    return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
  } else {
    return VK_ERROR_EXTENSION_NOT_PRESENT;
  }

  //---------------------------
}
void VK_validation::DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator) {
  //---------------------------

  auto func = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
  if (func != nullptr) {
    func(instance, debugMessenger, pAllocator);
  }

  //---------------------------
}
