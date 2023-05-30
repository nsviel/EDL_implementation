#ifndef VK_CLASS_H
#define VK_CLASS_H

#include "../Struct/struct_frame.h"
#include "../../../common.h"

class Engine;
class Param_vulkan;
class VK_device;


class VK_synchronization
{
public:
  //Constructor / Destructor
  VK_synchronization(Engine* engineManager);
  ~VK_synchronization();

public:
  //Main functions
  void create_sync_objects(Frame_inflight* frame);
  void clean_sync_obj(Frame_inflight* frame);

private:
  Engine* engineManager;
  Param_vulkan* param_vulkan;
  VK_device* vk_device;

  std::vector<VkSemaphore> semvec_image_available;
  std::vector<VkSemaphore> semvec_render_finish;
  std::vector<VkFence> fenvec_inFlight;
};

#endif
