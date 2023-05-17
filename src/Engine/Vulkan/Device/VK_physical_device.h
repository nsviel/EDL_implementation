#ifndef VK_PHYSICAL_DEVICE_H
#define VK_PHYSICAL_DEVICE_H

#include "../../../common.h"

class Node_engine;
class Engine;
class VK_window;
class VK_instance;


class VK_physical_device
{
public:
  //Constructor / Destructor
  VK_physical_device(Engine* node_engine);
  ~VK_physical_device();

public:
  //Main functions
  void init_device();
  void select_physical_device();
  void compute_extent();

  //Subfunctions
  bool is_device_suitable(VkPhysicalDevice physical_device);
  bool check_extension_support(VkPhysicalDevice physical_device);

  //Specific info retrieval
  int find_queue_family_graphics(VkPhysicalDevice physical_device);
  int find_queue_family_presentation(VkPhysicalDevice physical_device);

  VkSurfaceCapabilitiesKHR find_surface_capability(VkPhysicalDevice physical_device);
  vector<VkSurfaceFormatKHR> find_surface_format(VkPhysicalDevice physical_device);
  vector<VkPresentModeKHR> find_presentation_mode(VkPhysicalDevice physical_device);

  inline VkPhysicalDevice get_physical_device(){return physical_device;}
  inline vector<char*> get_required_extension(){return required_extension;}
  inline VkExtent2D get_extent(){return extent;}

private:
  Engine* engineManager;
  VK_window* vk_window;
  VK_instance* vk_instance;

  VkPhysicalDevice physical_device;
  vector<char*> required_extension;
  VkExtent2D extent;
};

#endif
