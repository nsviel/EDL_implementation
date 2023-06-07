#ifndef STRUCT_COMMAND_H
#define STRUCT_COMMAND_H

#include "../../../common.h"


struct Struct_submit_command{
  //---------------------------

  VkCommandBuffer command_buffer;

  VkSemaphore semaphore_to_wait;
  VkSemaphore semaphore_to_run;
  VkFence fence = VK_NULL_HANDLE;

  //---------------------------
};


#endif
