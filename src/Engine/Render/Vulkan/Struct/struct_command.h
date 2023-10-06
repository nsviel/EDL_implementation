#ifndef STRUCT_COMMAND_H
#define STRUCT_COMMAND_H

#include <Specific/common.h>


struct Struct_submit_command{
  //---------------------------

  VkCommandBuffer command_buffer;
  VkPipelineStageFlags wait_stage;

  VkSemaphore semaphore_to_wait;
  VkSemaphore semaphore_to_run;
  VkFence fence = VK_NULL_HANDLE;

  //---------------------------
};

struct Struct_submit_commands{
  //---------------------------

  std::vector<VkCommandBuffer> vec_command_buffer;
  std::vector<VkPipelineStageFlags> vec_wait_stage;

  std::vector<VkSemaphore> vec_semaphore_to_wait;
  std::vector<VkSemaphore> vec_semaphore_to_run;

  VkFence fence = VK_NULL_HANDLE;

  //---------------------------
};


#endif
