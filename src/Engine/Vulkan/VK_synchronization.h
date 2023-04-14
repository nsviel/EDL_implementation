#ifndef VK_CLASS_H
#define VK_CLASS_H

#include <vulkan/vulkan.h>

#include "../../common.h"

class Engine_vulkan;


class VK_synchronization
{
public:
  //Constructor / Destructor
  VK_synchronization(Engine_vulkan* engine_vulkan);
  ~VK_synchronization();

public:
  //Main functions
  void create_sync_objects();

private:
  Engine_vulkan* engine_vulkan;
  
  std::vector<VkSemaphore> imageAvailableSemaphores;
  std::vector<VkSemaphore> renderFinishedSemaphores;
  std::vector<VkFence> inFlightFences;
};

#endif
