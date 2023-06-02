#ifndef STRUCT_IMAGE_H
#define STRUCT_IMAGE_H

#include "struct_attachment.h"
#include "../../../common.h"


struct Frame{
  //---------------------------

  //Main object
  VkFramebuffer fbo;
  VkCommandBuffer command_buffer;

  //Attachment
  Struct_attachment color;
  Struct_attachment location;
  Struct_attachment normal;
  Struct_attachment depth;

  //Synchronisation
  VkSemaphore semaphore_render_finished;
  VkSemaphore semaphore_image_available;
  VkFence fence;

  //---------------------------
};

struct Frame_set{
  //---------------------------

  //Function
  Frame* get_frame_inflight(){return vec_frame[frame_inflight_ID];}
  Frame* get_frame_swapchain(){return vec_frame[frame_sawpchain_ID];}

  //Element
  std::vector<Frame*> vec_frame;
  uint32_t frame_sawpchain_ID = 0;
  uint32_t frame_inflight_ID = 0;

  //---------------------------
};


#endif
