#ifndef STRUCT_SWAPCHAIN_H
#define STRUCT_SWAPCHAIN_H

#include "struct_image.h"
#include "../../../common.h"


struct Struct_swapchain{

  Image* get_current_image(){return vec_image[current_image];}
  Frame* get_current_frame(){return vec_frame[current_frame];}

  uint32_t current_image = 0;
  uint32_t current_frame = 0;

  vector<Image*> vec_image;
  vector<Frame*> vec_frame;
  vector<VkImage> vec_swapchain_image;
  VkSwapchainKHR swapchain;
};


#endif
