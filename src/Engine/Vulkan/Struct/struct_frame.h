#ifndef STRUCT_IMAGE_H
#define STRUCT_IMAGE_H

#include "struct_attachment.h"
#include "../../../common.h"


struct Frame{
  //---------------------------

  int ID;

  //Main object
  VkFramebuffer fbo;

  //Attachment
  Struct_image color;
  Struct_image location;
  Struct_image normal;
  Struct_image depth;

  //Synchronisation
  VkSemaphore semaphore_scene_ready;
  VkSemaphore semaphore_render_ready;
  VkSemaphore semaphore_presentation;
  VkSemaphore semaphore_ui_ready;
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
