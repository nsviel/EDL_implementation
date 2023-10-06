#ifndef STRUCT_IMAGE_H
#define STRUCT_IMAGE_H

#include <Specific/common.h>
#include "struct_image.h"


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
  VkSemaphore semaphore_image_ready;
  VkSemaphore semaphore_scene_ready;
  VkSemaphore semaphore_edl_ready;
  VkSemaphore semaphore_psr_ready;
  VkSemaphore semaphore_ui_ready;
  VkFence fence;

  //---------------------------
};


#endif
