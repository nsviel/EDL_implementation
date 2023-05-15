#ifndef VK_DEPTH_H
#define VK_DEPTH_H

#include "../../../common.h"

#include <vulkan/vulkan.h>

class Engine;
class VK_device;
class VK_texture;
class VK_swapchain;
class VK_physical_device;


class VK_depth
{
public:
  //Constructor / Destructor
  VK_depth(Engine* engineManager);
  ~VK_depth();

public:
  //Main functions
  void create_depth_resources();
  void cleanup();

  //Subfunctions
  VkFormat find_supported_format(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
  VkFormat find_depth_format();
  bool find_stencil_component(VkFormat format);

  inline VkImageView get_depthImageView(){return depth_image_view;};

private:
  Engine* engineManager;
  VK_device* vk_device;
  VK_texture* vk_texture;
  VK_swapchain* vk_swapchain;
  VK_physical_device* vk_physical_device;

  VkImage depth_image;
  VkDeviceMemory depth_image_mem;
  VkImageView depth_image_view;
};

#endif
