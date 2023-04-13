#ifndef VK_INSTANCE_H
#define VK_INSTANCE_H

#include <vulkan/vulkan.h>

#include "../../common.h"

class Node_engine;

//List of all validation layers
const std::vector<const char*> validation_layers = {
    "VK_LAYER_KHRONOS_validation"
};



class VK_instance
{
public:
  //Constructor / Destructor
  VK_instance();
  ~VK_instance();

public:
  //Main functions
  void create_instance();

  //Validation layers
  bool check_validationLayer_support();
  std::vector<const char*> get_required_extensions();
  void setup_debug_messenger();

  inline VkInstance get_vk_instance(){return instance;}

private:
  VkInstance instance;
  VkDebugUtilsMessengerEXT debugMessenger;

  bool with_validation_layer = true;
};

#endif
