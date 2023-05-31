#ifndef VK_VALIDATION_H
#define VK_VALIDATION_H

#include "../Struct/struct_validation.h"
#include "../../../common.h"

class VK_engine;
class Param_vulkan;
class VK_instance;


class VK_validation
{
public:
  //Constructor / Destructor
  VK_validation(VK_engine* vk_engine);
  ~VK_validation();

public:
  //Main functions
  void create_validation_layer();
  void cleanup();

  //Extension
  void* find_validation_extension();
  void* extension_debug(void* ptr);
  void* extension_feature(void* ptr);

  //Subfunction
  bool check_validation_layer_support();
  VkResult create_debug_EXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);
  void destroy_debug_EXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);

  inline vector<const char*> get_validation_layers(){return validation_layers;};

private:
  Param_vulkan* param_vulkan;
  VK_instance* vk_instance;

  vector<const char*> validation_layers;
  bool with_validation_layer;
  bool with_best_practice;
  bool with_shader_printf;

  VkDebugUtilsMessengerCreateInfoEXT EXT_debug_info;
  VkDebugUtilsMessengerEXT EXT_debug;
  vector<VkValidationFeatureEnableEXT> EXT_enables;
  VkValidationFeaturesEXT EXT_feature;
};

#endif
