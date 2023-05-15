#ifndef VK_DEVICE_H
#define VK_DEVICE_H

#include "../../../common.h"

class Engine;
class VK_physical_device;


class VK_device
{
public:
  //Constructor / Destructor
  VK_device(Engine* node_engine);
  ~VK_device();

public:
  //Main functions
  void create_logical_device();
  void cleanup();

  inline VkDevice get_device(){return device;}
  inline VkQueue get_queue_graphics(){return queue_graphics;}
  inline VkQueue get_queue_presentation(){return queue_presentation;}

private:
  VK_physical_device* vk_physical_device;

  VkDevice device;
  VkQueue queue_graphics;
  VkQueue queue_presentation;
};

#endif
