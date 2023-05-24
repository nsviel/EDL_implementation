#ifndef VK_INSTANCE_H
#define VK_INSTANCE_H

#include "../../../common.h"

class Engine;
class Param_vulkan;


class VK_instance
{
public:
  //Constructor / Destructor
  VK_instance(Engine* engineManager);
  ~VK_instance();

public:
  //Main functions
  void create_instance();
  void cleanup();

private:
  Engine* engineManager;
  Param_vulkan* param_vulkan;
};

#endif
