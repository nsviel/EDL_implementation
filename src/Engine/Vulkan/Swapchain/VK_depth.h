#ifndef VK_DEPTH_H
#define VK_DEPTH_H

#include "../VK_struct.h"
#include "../../../common.h"

#include <vulkan/vulkan.h>

class Engine;
class VK_device;
class VK_texture;
class VK_swapchain;


class VK_depth
{
public:
  //Constructor / Destructor
  VK_depth(Engine* engineManager);
  ~VK_depth();

public:
  //Main functions
  void create_depth_resources();

  //Subfunctions
  VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
  VkFormat findDepthFormat();
  bool hasStencilComponent(VkFormat format);
  void cleanup();

  inline VkImageView get_depthImageView(){return depthImageView;};

private:
  Engine* engineManager;
  VK_device* vk_device;
  VK_texture* vk_texture;
  VK_swapchain* vk_swapchain;

  VkImage depthImage;
  VkDeviceMemory depthImageMemory;
  VkImageView depthImageView;
};

#endif
