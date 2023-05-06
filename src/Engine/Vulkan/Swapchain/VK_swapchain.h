#ifndef VK_SWAPCHAIN_H
#define VK_SWAPCHAIN_H

#include "../VK_struct.h"
#include "../../../common.h"

class Engine;
class VK_window;
class VK_device;


class VK_swapchain
{
public:
  //Constructor / Destructor
  VK_swapchain(Engine* engineManager);
  ~VK_swapchain();

public:
  //Main functions
  void init_swapchain();
  void create_swapChain();
  void create_image_views();

  //Swap chian settings
  struct_swapChain_details find_swapChain_details(VkPhysicalDevice device);
  VkSurfaceFormatKHR swapChain_surface_format(const std::vector<VkSurfaceFormatKHR>& availableFormats);
  VkPresentModeKHR swapChain_presentation_mode(const std::vector<VkPresentModeKHR>& availablePresentModes);
  VkExtent2D swapChain_extent_setting(const VkSurfaceCapabilitiesKHR& capabilities);
  void recreate_swapChain();
  void cleanup();

  inline VkSwapchainKHR get_swapChain(){return swapChain;}
  inline VkFormat get_swapChain_image_format(){return swapChain_image_format;}
  inline VkExtent2D get_swapChain_extent(){return swapchain_extent;}

  inline std::vector<VkImage> get_swapChain_images(){return swapChain_images;}
  inline std::vector<VkImageView> get_swapChain_image_views(){return swapChain_image_views;}

private:
  Engine* engineManager;
  VK_window* vk_window;
  VK_device* vk_device;

  VkSwapchainKHR swapChain;
  VkFormat swapChain_image_format;
  VkExtent2D swapchain_extent;

  std::vector<VkImage> swapChain_images;
  std::vector<VkImageView> swapChain_image_views;
};

#endif
