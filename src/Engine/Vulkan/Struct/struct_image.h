#ifndef STRUCT_IMAGE_H
#define STRUCT_IMAGE_H

#include "../../../common.h"


struct Image{
  //Image
  VkImage image;
  VkImageView image_view;

  //Depth
  VkImage depth;
  VkImageView depth_view;
  VkDeviceMemory depth_memory;

  //Rendering
  vector<VkFramebuffer> fbo_vec;

  //Associated objects
  VkCommandBuffer command_buffer;
  VkDescriptorSet descriptor_set;
  VkFence fence_inflight;
  VkSemaphore semaphore_render_finished;
  VkSemaphore semaphore_image_available;
};


#endif
