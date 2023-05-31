#ifndef STRUCT_IMAGE_H
#define STRUCT_IMAGE_H

#include "struct_attachment.h"
#include "../../../common.h"


struct Frame_renderpass{
  //---------------------------

  //Main object
  VkFramebuffer fbo;
  VkRenderPass renderpass;

  //Attachment
  Struct_attachment color;
  Struct_attachment location;
  Struct_attachment normal;
  Struct_attachment depth;

  //---------------------------
};

struct Frame_inflight{
  //---------------------------

  int ID_frame;

  VkCommandBuffer command_buffer;
  VkSemaphore semaphore_render_finished;
  VkSemaphore semaphore_image_available;
  VkFence fence;

  //---------------------------
};


#endif
