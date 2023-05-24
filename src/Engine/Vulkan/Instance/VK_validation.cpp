#include "VK_validation.h"
#include "VK_instance.h"

#include "../Engine.h"
#include "../Param_vulkan.h"


//Constructor / Destructor
VK_validation::VK_validation(Engine* engineManager){
  //---------------------------

  this->param_vulkan = engineManager->get_param_vulkan();
  this->vk_instance = engineManager->get_vk_instance();

  this->param_vulkan->extension_instance.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
  this->param_vulkan->extension_instance.push_back(VK_EXT_VALIDATION_FEATURES_EXTENSION_NAME);
  this->validation_layers = {"VK_LAYER_KHRONOS_validation"};
  this->with_validation_layer = true;
  this->with_best_practice = false;

  //---------------------------
}
VK_validation::~VK_validation(){}

//Main function
void VK_validation::create_validation_layer(){
  //---------------------------

  if(!with_validation_layer) return;

  VkDebugUtilsMessengerCreateInfoEXT createInfo{};
  createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
  createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
  createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
  createInfo.pfnUserCallback = debugCallback;

  VkResult result = create_debug_EXT(param_vulkan->instance, &createInfo, nullptr, &EXT_debug);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to set up debug messenger!");
  }

  //---------------------------
}
bool VK_validation::check_validation_layer(){
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
  //---------------------------

  if(with_validation_layer){
    destroy_debug_EXT(param_vulkan->instance, EXT_debug, nullptr);
  }

  //---------------------------
}

//Subfunction
VkResult VK_validation::create_debug_EXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger) {
  //---------------------------

  auto func = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
  if(func != nullptr){
    return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
  }else{
    return VK_ERROR_EXTENSION_NOT_PRESENT;
  }

  //---------------------------
}
void VK_validation::destroy_debug_EXT(VkInstance instance, VkDebugUtilsMessengerEXT EXT_debug, const VkAllocationCallbacks* pAllocator) {
  //---------------------------

  auto func = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
  if(func != nullptr){
    func(instance, EXT_debug, pAllocator);
  }

  //---------------------------
}
void VK_validation::fill_instance_info(VkInstanceCreateInfo& createInfo){
  //---------------------------

  if(with_validation_layer && check_validation_layer()){
    //Debug EXT
    EXT_debug_info = {};
    EXT_debug_info.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    EXT_debug_info.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
    EXT_debug_info.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
    EXT_debug_info.pfnUserCallback = debugCallback;

    //Best practice EXT
    if(with_best_practice){
      EXT_enables.push_back(VK_VALIDATION_FEATURE_ENABLE_BEST_PRACTICES_EXT);
      EXT_feature = {};
      EXT_feature.sType = VK_STRUCTURE_TYPE_VALIDATION_FEATURES_EXT;
      EXT_feature.enabledValidationFeatureCount = 1;
      EXT_feature.pEnabledValidationFeatures = EXT_enables.data();

      EXT_debug_info.pNext =&EXT_feature;
    }

    //Fill info
    createInfo.enabledLayerCount = static_cast<uint32_t>(validation_layers.size());
    createInfo.ppEnabledLayerNames = validation_layers.data();
    createInfo.pNext = &EXT_debug_info;
  }else{
    createInfo.enabledLayerCount = 0;
    createInfo.pNext = nullptr;
  }

  //---------------------------
}
