#ifndef STRUCT_SWAPCHAIN_H
#define STRUCT_SWAPCHAIN_H

#include "struct_frame.h"
#include <Specific/common.h>


struct Struct_swapchain{
  //---------------------------

  //Swapchain element
  VkSwapchainKHR swapchain;

  //Swapchain image
  vector<VkImage> vec_swapchain_image;

  //Swapchain frame
  Frame* get_frame_current(){return vec_frame[frame_current_ID];}
  Frame* get_frame_inflight(){return vec_frame[frame_inflight_ID];}
  uint32_t frame_current_ID = 0;
  uint32_t frame_inflight_ID = 0;
  std::vector<Frame*> vec_frame;

  //---------------------------
};


#endif
