#ifndef VK_INSTANCE_H
#define VK_INSTANCE_H

#include "../../../common.h"

class VK_engine;
class Param_vulkan;


class VK_instance
{
public:
  //Constructor / Destructor
  VK_instance(VK_engine* vk_engine);
  ~VK_instance();

public:
  //Main functions
  void create_instance();
  void cleanup();

private:
  VK_engine* vk_engine;
  Param_vulkan* param_vulkan;
};

#endif
