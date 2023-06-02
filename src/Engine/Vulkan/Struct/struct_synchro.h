#ifndef STRUCT_SYNCHRO_H
#define STRUCT_SYNCHRO_H

#include "struct_attachment.h"
#include "../../../common.h"


struct Struct_synchro{
  //---------------------------

  VkSemaphore semaphore_render_finished;
  VkSemaphore semaphore_image_available;
  VkFence fence;

  //---------------------------
};


#endif
