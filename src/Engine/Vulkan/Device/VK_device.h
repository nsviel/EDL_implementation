#ifndef VK_DEVICE_H
#define VK_DEVICE_H

#include "../Struct/struct_queue.h"
#include "../Struct/struct_swapchain.h"
#include "../../../common.h"

class Node_engine;
class Engine;
class VK_window;
class VK_instance;

//List of required device extensions
const std::vector<const char*> required_extensions = {
  VK_KHR_SWAPCHAIN_EXTENSION_NAME
};


class VK_device
{
public:
  //Constructor / Destructor
  VK_device(Engine* node_engine);
  ~VK_device();

public:
  //Main functions
  void init_device();
  void create_logical_device();
  void select_physical_device();
  void cleanup();

  //Subfunctions
  bool is_device_suitable(VkPhysicalDevice device);
  bool check_extension_support(VkPhysicalDevice device);

  //Specific info retrieval
  struct_queueFamily_indices find_queue_families(VkPhysicalDevice device);
  struct_swapChain_details find_swapChain_details(VkPhysicalDevice device);

  inline VkPhysicalDevice get_physical_device(){return physical_device;}
  inline VkDevice get_device(){return device;}
  inline VkQueue get_queue_graphics(){return queue_graphics;}
  inline VkQueue get_queue_presentation(){return queue_presentation;}

private:
  VK_window* vk_window;
  Engine* engineManager;
  VK_instance* vk_instance;

  VkDevice device;
  VkPhysicalDevice physical_device;
  VkQueue queue_graphics;
  VkQueue queue_presentation;
};

#endif
