#ifndef VK_SWAPCHAIN_H
#define VK_SWAPCHAIN_H

#include "../../../common.h"

class Engine;
class Param_vulkan;
class VK_window;
class VK_device;
class VK_physical_device;


class VK_swapchain
{
public:
  //Constructor / Destructor
  VK_swapchain(Engine* engineManager);
  ~VK_swapchain();

public:
  //Main function
  void recreate_swapChain();
  void clean_swapchain();

  //Swap chain creation
  void create_swapchain();
  void create_swapchain_surface(VkSwapchainCreateInfoKHR& createInfo);
  void create_swapchain_family(VkSwapchainCreateInfoKHR& createInfo);
  void create_swapchain_presentation(VkSwapchainCreateInfoKHR& createInfo);
  void create_swapchain_image(VkSwapchainKHR swapchain, unsigned int min_image_count);

  //Swap chain parameter
  VkSurfaceFormatKHR swapchain_surface_format(const std::vector<VkSurfaceFormatKHR>& availableFormats);
  VkPresentModeKHR swapchain_presentation_mode(const std::vector<VkPresentModeKHR>& availablePresentModes);

private:
  Engine* engineManager;
  Param_vulkan* param_vulkan;
  VK_window* vk_window;
  VK_device* vk_device;
  VK_physical_device* vk_physical_device;
};

#endif
