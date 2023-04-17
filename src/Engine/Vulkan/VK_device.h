#ifndef VK_DEVICE_H
#define VK_DEVICE_H

#include <vulkan/vulkan.h>

#include "VK_struct.h"

#include "../../common.h"


class Node_engine;
class Engine_vulkan;
class VK_window;
class VK_instance;


class VK_device
{
public:
  //Constructor / Destructor
  VK_device(Engine_vulkan* node_engine);
  ~VK_device();

public:
  //Main functions
  void create_logical_device();
  void select_physical_device();
  void cleanup();

  struct_queueFamily_indices find_queue_families(VkPhysicalDevice device);
  bool is_device_suitable(VkPhysicalDevice device);
  bool check_extension_support(VkPhysicalDevice device);
  struct_swapChain_details find_swapChain_details(VkPhysicalDevice device);

  inline VkPhysicalDevice get_physical_device(){return physical_device;}
  inline VkDevice get_device(){return device;}
  inline VkQueue get_queue_graphics(){return queue_graphics;}
  inline VkQueue get_queue_presentation(){return queue_presentation;}

private:
  VK_window* vk_window;
  Engine_vulkan* engine_vulkan;
  VK_instance* vk_instance;

  VkDevice device;
  VkPhysicalDevice physical_device;

  VkQueue queue_graphics;
  VkQueue queue_presentation;
};

#endif
