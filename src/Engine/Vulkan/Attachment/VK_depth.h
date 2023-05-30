#ifndef VK_DEPTH_H
#define VK_DEPTH_H

#include "../Struct/struct_frame.h"
#include "../../../common.h"

class Engine;
class Param_vulkan;
class VK_texture;


class VK_depth
{
public:
  //Constructor / Destructor
  VK_depth(Engine* engineManager);
  ~VK_depth();

public:
  //Main functions
  void create_depth_attachment(Frame_swapchain* image);
  void clean_depth_attachment(Frame_swapchain* image);

  //Subfunctions
  bool find_stencil_component(VkFormat format);
  VkFormat find_supported_format(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
  VkFormat find_depth_format();

private:
  Engine* engineManager;
  Param_vulkan* param_vulkan;
  VK_texture* vk_texture;
};

#endif
