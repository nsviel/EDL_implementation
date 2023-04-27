#ifndef VK_INSTANCE_H
#define VK_INSTANCE_H

#include "../VK_struct.h"

#include "../../../common.h"

#include <vulkan/vulkan.h>

class Node_engine;


static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,VkDebugUtilsMessageTypeFlagsEXT messageType,const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,void* pUserData){
  //---------------------------

  std::cerr << "--------------------------" << std::endl;
  std::cerr << "[\033[1;32mVL\033[0m] " << pCallbackData->pMessage << std::endl;

  //---------------------------
  return VK_FALSE;
}




class VK_instance
{
public:
  //Constructor / Destructor
  VK_instance();
  ~VK_instance();

public:
  //Main functions
  void create_instance();
  void create_validationLayer();
  void cleanup();

  //Validation layers
  bool check_validationLayer_support(std::vector<const char*> validationLayers);
  std::vector<const char*> get_required_extensions();
  VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);
  void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);
  void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);

  inline VkInstance get_instance(){return instance;}

private:
  VkInstance instance;
  VkDebugUtilsMessengerEXT debugMessenger;

  bool with_validation_layer = true;
};

#endif
