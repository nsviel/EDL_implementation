#ifndef VK_CLASS_H
#define VK_CLASS_H

#include <vulkan/vulkan.h>

#include "../../../common.h"

class Engine;
class VK_device;


class VK_synchronization
{
public:
  //Constructor / Destructor
  VK_synchronization(Engine* engineManager);
  ~VK_synchronization();

public:
  //Main functions
  void create_sync_objects();
  void cleanup();

  inline std::vector<VkSemaphore> get_semvec_image_available(){return semvec_image_available;}
  inline std::vector<VkSemaphore> get_semvec_render_finish(){return semvec_render_finish;}
  inline std::vector<VkFence> get_fenvec_inFlight(){return fenvec_inFlight;}

private:
  Engine* engineManager;
  VK_device* vk_device;

  std::vector<VkSemaphore> semvec_image_available;
  std::vector<VkSemaphore> semvec_render_finish;
  std::vector<VkFence> fenvec_inFlight;
};

#endif
