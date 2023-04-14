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
  void cleanup();

  inline std::vector<VkSemaphore> get_imageAvailableSemaphores(){return imageAvailableSemaphores;}
  inline std::vector<VkSemaphore> get_renderFinishedSemaphores(){return renderFinishedSemaphores;}
  inline std::vector<VkFence> get_inFlightFences(){return inFlightFences;}

private:
  Engine_vulkan* engine_vulkan;

  std::vector<VkSemaphore> imageAvailableSemaphores;
  std::vector<VkSemaphore> renderFinishedSemaphores;
  std::vector<VkFence> inFlightFences;
};

#endif
