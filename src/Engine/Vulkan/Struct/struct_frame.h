#ifndef STRUCT_IMAGE_H
#define STRUCT_IMAGE_H

#include "struct_attachment.h"
#include "../../../common.h"


struct Frame{
  //---------------------------

  //Main object
  VkFramebuffer fbo;

  //Attachment
  Struct_frame_attachment color;
  Struct_frame_attachment location;
  Struct_frame_attachment normal;
  Struct_frame_attachment depth;

  //Synchronisation
  VkSemaphore semaphore_scene;
  VkSemaphore semaphore_drawing;
  VkSemaphore semaphore_presentation;
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
