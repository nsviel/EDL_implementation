#ifndef VK_PHYSICAL_DEVICE_H
#define VK_PHYSICAL_DEVICE_H

#include "../Struct/struct_queue.h"
#include "../Struct/struct_swapchain.h"
#include "../../../common.h"

class Node_engine;
class Engine;
class VK_window;
class VK_instance;

//List of required device extensions
const std::vector<const char*> required_vk_extensions = {
  VK_KHR_SWAPCHAIN_EXTENSION_NAME
};


class VK_physical_device
{
public:
  //Constructor / Destructor
  VK_physical_device(Engine* node_engine);
  ~VK_physical_device();

public:
  //Main functions
  void select_physical_device();

  //Subfunctions
  bool is_device_suitable(VkPhysicalDevice device);
  bool check_extension_support(VkPhysicalDevice device);

  //Specific info retrieval
  struct_queueFamily_indices find_queue_families(VkPhysicalDevice device);
  struct_swapChain_details find_swapChain_details(VkPhysicalDevice device);

  inline VkPhysicalDevice get_physical_device(){return physical_device;}

private:
  VK_window* vk_window;
  Engine* engineManager;
  VK_instance* vk_instance;

  VkPhysicalDevice physical_device;
};

#endif
