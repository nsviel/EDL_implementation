#ifndef VK_SWAPCHAIN_H
#define VK_SWAPCHAIN_H

#include "../../../common.h"

class Engine;
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
  //Main functions
  void init_swapchain();

  //Swap chain creation
  void create_swapChain();
  void create_image_views();
  void recreate_swapChain();
  void cleanup();

  //Swap chian parameter
  VkSurfaceFormatKHR swapChain_surface_format(const std::vector<VkSurfaceFormatKHR>& availableFormats);
  VkPresentModeKHR swapChain_presentation_mode(const std::vector<VkPresentModeKHR>& availablePresentModes);
  VkExtent2D swapChain_extent_setting(const VkSurfaceCapabilitiesKHR& capabilities);

  inline VkSwapchainKHR get_swapChain(){return swapChain;}
  inline VkFormat get_swapChain_image_format(){return swapChain_image_format;}
  inline VkExtent2D get_swapChain_extent(){return swapchain_extent;}

  inline std::vector<VkImage> get_swapChain_images(){return swapChain_images;}
  inline std::vector<VkImageView> get_swapChain_image_views(){return swapChain_image_views;}

private:
  Engine* engineManager;
  VK_window* vk_window;
  VK_device* vk_device;
  VK_physical_device* vk_physical_device;

  VkSwapchainKHR swapChain;
  VkFormat swapChain_image_format;
  VkExtent2D swapchain_extent;

  std::vector<VkImage> swapChain_images;
  std::vector<VkImageView> swapChain_image_views;
};

#endif
