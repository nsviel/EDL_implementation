#ifndef VK_DEVICE_H
#define VK_DEVICE_H

#include "../../../common.h"

class VK_engine;
class Param_vulkan;
class VK_physical_device;


class VK_device
{
public:
  //Constructor / Destructor
  VK_device(VK_engine* vk_engine);
  ~VK_device();

public:
  //Main functions
  void create_logical_device();
  void cleanup();

private:
  Param_vulkan* param_vulkan;
  VK_physical_device* vk_physical_device;
};

#endif
