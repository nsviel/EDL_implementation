#include "VK_validation.h"
#include "VK_instance.h"

#include "../Engine.h"
#include "../Param_vulkan.h"


//Constructor / Destructor
VK_validation::VK_validation(Engine* engineManager){
  //---------------------------

  this->param_vulkan = engineManager->get_param_vulkan();
  this->vk_instance = engineManager->get_vk_instance();

  this->param_vulkan->instance.extension.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
  this->param_vulkan->instance.extension.push_back(VK_EXT_VALIDATION_FEATURES_EXTENSION_NAME);
  this->validation_layers = {"VK_LAYER_KHRONOS_validation"};
  this->with_validation_layer = true;
  this->with_best_practice = false;
  this->with_shader_printf = true;

  //---------------------------
}
VK_validation::~VK_validation(){}

//Main function
void VK_validation::create_validation_layer(){
  if(!with_validation_layer) return;
  //---------------------------

//COMPRENDRE POURQUOI YA 2 FOIS CES INSTRUCTIONS
  VkDebugUtilsMessengerCreateInfoEXT create_info{};
  create_info.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
  create_info.messageSeverity =
    VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | \
    VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | \
    VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT | \
    VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT;
  create_info.messageType =
    VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | \
    VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
  create_info.pfnUserCallback = callback_debug;

  VkResult result = create_debug_EXT(param_vulkan->instance.instance, &create_info, nullptr, &EXT_debug);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to set up debug messenger!");
  }

  //---------------------------
}
void VK_validation::cleanup(){
  //---------------------------

  if(with_validation_layer){
    destroy_debug_EXT(param_vulkan->instance.instance, EXT_debug, nullptr);
  }

  //---------------------------
}

//Extension
void* VK_validation::find_validation_extension(){
  //---------------------------

  if(with_validation_layer && check_validation_layer_support()){
    void* ptr_debug = extension_debug(nullptr);
    void* ptr_feature = extension_feature(ptr_debug);

    return ptr_feature;
  }

  //---------------------------
  return nullptr;
}
void* VK_validation::extension_debug(void* ptr){
  //---------------------------

  EXT_debug_info = {};
  EXT_debug_info.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
  EXT_debug_info.messageSeverity =
    VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | \
    VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | \
    VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
  EXT_debug_info.messageType =
    VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | \
    VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
  EXT_debug_info.pfnUserCallback = callback_debug;
  EXT_debug_info.pNext = ptr;

  //---------------------------
  return &EXT_debug_info;
}
void* VK_validation::extension_feature(void* ptr){
  //---------------------------

  if(with_best_practice){
    EXT_enables.push_back(VK_VALIDATION_FEATURE_ENABLE_BEST_PRACTICES_EXT);
  }
  if(with_shader_printf){
    EXT_enables.push_back(VK_VALIDATION_FEATURE_ENABLE_DEBUG_PRINTF_EXT);
  }

  EXT_feature = {};
  EXT_feature.sType = VK_STRUCTURE_TYPE_VALIDATION_FEATURES_EXT;
  EXT_feature.enabledValidationFeatureCount = static_cast<uint32_t>(EXT_enables.size());
  EXT_feature.pEnabledValidationFeatures = EXT_enables.data();
  EXT_feature.pNext = ptr;

  //---------------------------
  return &EXT_feature;
}

//Subfunction
bool VK_validation::check_validation_layer_support(){
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
