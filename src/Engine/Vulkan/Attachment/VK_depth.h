#ifndef VK_DEPTH_H
#define VK_DEPTH_H

#include "../Struct/struct_frame.h"
#include "../../../common.h"

class VK_engine;
class VK_param;
class VK_texture;


class VK_depth
{
public:
  //Constructor / Destructor
  VK_depth(VK_engine* vk_engine);
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
  VK_engine* vk_engine;
  VK_param* vk_param;
  VK_texture* vk_texture;
};

#endif
