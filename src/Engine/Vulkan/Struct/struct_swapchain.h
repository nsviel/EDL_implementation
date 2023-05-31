#ifndef STRUCT_SWAPCHAIN_H
#define STRUCT_SWAPCHAIN_H

#include "struct_frame.h"
#include "../../../common.h"


struct Struct_swapchain{
  //---------------------------

  Frame_swapchain* get_current_frame_swapchain(){return vec_frame_swapchain[current_frame_swapchain_ID];}
  Frame_inflight* get_current_frame_inflight(){return vec_frame_inflight[current_frame_inflight_ID];}

  uint32_t current_frame_swapchain_ID = 0;
  uint32_t current_frame_inflight_ID = 0;

  vector<Frame_swapchain*> vec_frame_swapchain;
  vector<Frame_inflight*> vec_frame_inflight;
  vector<VkImage> vec_swapchain_image;
  VkSwapchainKHR swapchain;

  //---------------------------
};


#endif
