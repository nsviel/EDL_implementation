#ifndef VK_DEVICE_H
#define VK_DEVICE_H

#include <vulkan/vulkan.h>

#include "../../common.h"

#ifndef STRUCT_FOO
#define STRUCT_FOO
struct struct_queueFamily_indices {
  std::optional<uint32_t> family_graphics;
  std::optional<uint32_t> family_presentation;
  bool is_complete() {
    return family_graphics.has_value() && family_presentation.has_value();
  }
};
struct struct_swapChain_details {
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> mode_presentation;
};

//List of required device extensions
const std::vector<const char*> required_extensions = {
  VK_KHR_SWAPCHAIN_EXTENSION_NAME
};
#endif

class Node_engine;
class Engine_vulkan;
class Engine_window;


class VK_device
{
public:
  //Constructor / Destructor
  VK_device(Node_engine* node_engine);
  ~VK_device();

public:
  //Main functions
  VkDevice create_logical_device();
  VkPhysicalDevice select_physical_device(VkInstance instance);


  struct_queueFamily_indices find_queue_families(VkPhysicalDevice device);
  bool is_device_suitable(VkPhysicalDevice device);
  bool check_extension_support(VkPhysicalDevice device);
  struct_swapChain_details find_swapChain_details(VkPhysicalDevice device);

  inline VkPhysicalDevice get_vk_gpu(){return physical_device;}
  inline VkDevice get_vk_device(){return device;}

private:
  Engine_window* engine_window;

  VkDevice device;
  VkPhysicalDevice physical_device;

  VkQueue queue_graphics;
  VkQueue queue_presentation;
};

#endif
