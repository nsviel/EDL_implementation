#ifndef VK_DEPTH_H
#define VK_DEPTH_H

#include "../Struct/struct_image.h"
#include "../../../common.h"

class Engine;
class VK_device;
class VK_texture;
class VK_swapchain;
class VK_physical_device;
class VK_image;


class VK_depth
{
public:
  //Constructor / Destructor
  VK_depth(Engine* engineManager);
  ~VK_depth();

public:
  //Main functions
  void create_depth_resource(Image* image);
  void clean_depth_resource(Image* image);

  //Subfunctions
  bool find_stencil_component(VkFormat format);
  VkFormat find_supported_format(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
  VkFormat find_depth_format();

private:
  Engine* engineManager;
  VK_device* vk_device;
  VK_texture* vk_texture;
  VK_swapchain* vk_swapchain;
  VK_physical_device* vk_physical_device;
  VK_image* vk_image;
};

#endif
