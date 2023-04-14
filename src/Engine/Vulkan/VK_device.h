#ifndef VK_DEVICE_H
#define VK_DEVICE_H

#include <vulkan/vulkan.h>

#include "VK_struct.h"

#include "../../common.h"


class Node_engine;
class Engine_vulkan;
class Engine_window;


class VK_device
{
public:
  //Constructor / Destructor
  VK_device(Engine_vulkan* node_engine);
  ~VK_device();

public:
  //Main functions
  VkDevice create_logical_device();
  VkPhysicalDevice select_physical_device(VkInstance instance);
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
  Engine_window* engine_window;
  Engine_vulkan* engine_vulkan;

  VkDevice device;
  VkPhysicalDevice physical_device;

  VkQueue queue_graphics;
  VkQueue queue_presentation;
};

#endif
