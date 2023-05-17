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
};

struct Frame{
  int ID_frame;
  int ID_draw;

  VkDescriptorSet descriptor_set;
  VkCommandBuffer command_buffer;

  VkSemaphore semaphore_render_finished;
  VkSemaphore semaphore_image_available;
  VkFence fence_inflight;
};


#endif
