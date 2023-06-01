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

  //---------------------------
};


#endif
