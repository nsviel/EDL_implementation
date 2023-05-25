#ifndef VK_DEPTH_H
#define VK_DEPTH_H

#include "../Struct/struct_image.h"
#include "../../../common.h"

class Engine;
class Param_vulkan;
class VK_physical_device;


class VK_depth
{
public:
  //Constructor / Destructor
  VK_depth(Engine* engineManager);
  ~VK_depth();

public:
  //Main functions
  void create_depth_attachment(Image* image);
  void clean_depth_attachment(Image* image);

  //Subfunctions
  bool find_stencil_component(VkFormat format);
  VkFormat find_supported_format(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
  VkFormat find_depth_format();

private:
  Engine* engineManager;
  Param_vulkan* param_vulkan;
  VK_physical_device* vk_physical_device;
};

#endif
