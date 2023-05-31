#ifndef STRUCT_SWAPCHAIN_H
#define STRUCT_SWAPCHAIN_H

#include "struct_frame.h"
#include "../../../common.h"


struct Struct_swapchain{
  //---------------------------

  //Function
  Frame_inflight* get_current_frame_inflight(){return vec_frame_inflight[current_frame_inflight_ID];}

  //Swapchain element
  VkSwapchainKHR swapchain;

  //Swapchain in flight images
  vector<Frame_inflight*> vec_frame_inflight;
  uint32_t current_frame_inflight_ID = 0;

  //Intermediaire swapchain image
  vector<VkImage> vec_swapchain_image;

  //---------------------------
};


#endif
