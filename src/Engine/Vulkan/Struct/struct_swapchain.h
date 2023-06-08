#ifndef STRUCT_SWAPCHAIN_H
#define STRUCT_SWAPCHAIN_H

#include "struct_frame.h"
#include "../../../common.h"


struct Struct_swapchain{
  //---------------------------

  //Swapchain element
  VkSwapchainKHR swapchain;

  //Intermediaire swapchain image
  vector<VkImage> vec_swapchain_image;

  //Image
  Frame* get_current_frame(){return vec_frame[current_frame_ID];}
  uint32_t current_frame_ID = 0;
  std::vector<Frame*> vec_frame;

  //---------------------------
};


#endif
