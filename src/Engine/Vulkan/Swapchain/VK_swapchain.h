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
  void create_swapchain();
  void create_swapchain_surface(VkSwapchainCreateInfoKHR& createInfo);
  void create_swapchain_family(VkSwapchainCreateInfoKHR& createInfo);
  void create_swapchain_presentation(VkSwapchainCreateInfoKHR& createInfo);

  //Swap chain function
  void create_image_views();
  void recreate_swapChain();
  void cleanup();

  //Swap chain parameter
  VkSurfaceFormatKHR swapchain_surface_format(const std::vector<VkSurfaceFormatKHR>& availableFormats);
  VkPresentModeKHR swapchain_presentation_mode(const std::vector<VkPresentModeKHR>& availablePresentModes);
  void compute_extent(const VkSurfaceCapabilitiesKHR& capabilities);

  inline VkSwapchainKHR get_swapChain(){return swapchain;}
  inline VkExtent2D get_swapChain_extent(){return swapchain_extent;}

  inline VkFormat get_swapChain_image_format(){return swapchain_image_format;}
  inline std::vector<VkImage> get_swapChain_images(){return swapchain_images;}
  inline std::vector<VkImageView> get_swapChain_image_views(){return swapchain_image_views;}

private:
  Engine* engineManager;
  VK_window* vk_window;
  VK_device* vk_device;
  VK_physical_device* vk_physical_device;

  VkSwapchainKHR swapchain;
  VkExtent2D swapchain_extent;

  ON DOIT ICI VIRER CE QUI A TRAIT à image dans vk_image !!!!!!
  VkFormat swapchain_image_format;
  std::vector<VkImage> swapchain_images;
  std::vector<VkImageView> swapchain_image_views;
};

#endif
