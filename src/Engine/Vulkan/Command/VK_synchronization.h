#ifndef VK_CLASS_H
#define VK_CLASS_H

#include <vulkan/vulkan.h>

#include "../../../common.h"

class Engine;
class Param_engine;
class VK_device;
class VK_image;


class VK_synchronization
{
public:
  //Constructor / Destructor
  VK_synchronization(Engine* engineManager);
  ~VK_synchronization();

public:
  //Main functions
  void create_sync_objects();
  void fill_vec_frame();
  void cleanup();

private:
  Engine* engineManager;
  Param_engine* param_engine;
  VK_device* vk_device;
  VK_image* vk_image;

  std::vector<VkSemaphore> semvec_image_available;
  std::vector<VkSemaphore> semvec_render_finish;
  std::vector<VkFence> fenvec_inFlight;
};

#endif
