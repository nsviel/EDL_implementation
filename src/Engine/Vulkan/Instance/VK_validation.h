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
  void create_validation_layer();
  bool check_validation_layer();
  void cleanup();

  //Subfunction
  VkResult create_debug_EXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);
  void destroy_debug_EXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);
  void fill_instance_info(VkInstanceCreateInfo& createInfo);

private:
  Param_vulkan* param_vulkan;
  VK_instance* vk_instance;

  vector<const char*> validation_layers;
  bool with_validation_layer;
  bool with_best_practice;

  VkDebugUtilsMessengerCreateInfoEXT EXT_debug_info;
  VkDebugUtilsMessengerEXT EXT_debug;

  vector<VkValidationFeatureEnableEXT> EXT_enables;
  VkValidationFeaturesEXT EXT_feature;
};

#endif
