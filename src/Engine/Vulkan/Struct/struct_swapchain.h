#ifndef STRUCT_SWAPCHAIN_H
#define STRUCT_SWAPCHAIN_H

#include "struct_frame.h"
#include "../../../common.h"


struct Struct_swapchain{

  Frame_swapchain* get_current_image(){return vec_image[current_image_ID];}
  Frame_inflight* get_current_frame(){return vec_frame[current_frame_ID];}

  uint32_t current_image_ID = 0;
  uint32_t current_frame_ID = 0;

  vector<Frame_swapchain*> vec_image;
  vector<Frame_inflight*> vec_frame;
  vector<VkImage> vec_swapchain_image;
  VkSwapchainKHR swapchain;
};


#endif
