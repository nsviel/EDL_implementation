#ifndef VK_VALIDATION_H
#define VK_VALIDATION_H

#include "struct_callback.h"
#include "../../../common.h"

class Engine;
class Param_vulkan;
class VK_instance;


class VK_validation
{
public:
  //Constructor / Destructor
  VK_validation(Engine* engineManager);
  ~VK_validation();

public:
  //Main functions
  void create_validationLayer();
  bool check_validationLayer_support();
  void cleanup();

  //Subfunction
  VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);
  void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);
  void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);

  inline vector<const char*> get_validation_layers(){return validation_layers;}
  inline bool get_with_validation_layer(){return with_validation_layer;}

private:
  Param_vulkan* param_vulkan;
  VK_instance* vk_instance;

  VkDebugUtilsMessengerEXT debugMessenger;
  vector<const char*> validation_layers;
  bool with_validation_layer;
};

#endif
