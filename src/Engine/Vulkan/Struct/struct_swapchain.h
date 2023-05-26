#ifndef STRUCT_SWAPCHAIN_H
#define STRUCT_SWAPCHAIN_H

#include "struct_image.h"
#include "../../../common.h"


struct Struct_swapchain{

  Image* get_current_image(){return vec_image[current_image_ID];}
  Frame* get_current_frame(){return vec_frame[current_frame_ID];}

  uint32_t current_image_ID = 0;
  uint32_t current_frame_ID = 0;

  vector<Image*> vec_image;
  vector<Frame*> vec_frame;
  vector<VkImage> vec_swapchain_image;
  VkSwapchainKHR swapchain;
};


#endif
