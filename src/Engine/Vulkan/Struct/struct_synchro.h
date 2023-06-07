#ifndef STRUCT_SYNCHRO_H
#define STRUCT_SYNCHRO_H

#include "struct_attachment.h"
#include "../../../common.h"


struct Struct_synchro{
  //---------------------------

  VkSemaphore semaphore_drawOnQuad;
  VkSemaphore semaphore_presentation;
  VkFence fence;

  //---------------------------
};


#endif
