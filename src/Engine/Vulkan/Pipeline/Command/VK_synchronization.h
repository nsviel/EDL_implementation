#ifndef VK_CLASS_H
#define VK_CLASS_H

#include "../../Struct/struct_frame.h"
#include "../../../../common.h"

class VK_engine;
class VK_param;
class VK_device;


class VK_synchronization
{
public:
  //Constructor / Destructor
  VK_synchronization(VK_engine* vk_engine);
  ~VK_synchronization();

public:
  //Main functions
  void create_sync_objects(Frame* frame);
  void clean_sync_obj(Frame* frame);

private:
  VK_engine* vk_engine;
  VK_param* vk_param;
  VK_device* vk_device;

  std::vector<VkSemaphore> semvec_image_available;
  std::vector<VkSemaphore> semvec_render_finish;
  std::vector<VkFence> fenvec_inFlight;
};

#endif
