#ifndef STRUCT_SWAPCHAIN_H
#define STRUCT_SWAPCHAIN_H

#include "../../../common.h"


struct Struct_swapchain{
  uint32_t image_index;
  uint32_t frame_current;

  vector<VkImage> vec_swapchain_image;
  VkSwapchainKHR swapchain;
};


#endif
