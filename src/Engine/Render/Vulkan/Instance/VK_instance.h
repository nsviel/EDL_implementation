#ifndef VK_INSTANCE_H
#define VK_INSTANCE_H

#include <Specific/common.h>

class VK_engine;
class VK_param;


class VK_instance
{
public:
  //Constructor / Destructor
  VK_instance(VK_engine* vk_engine);
  ~VK_instance();

public:
  //Main functions
  void create_instance();
  void clean_instance();

private:
  VK_engine* vk_engine;
  VK_param* vk_param;
};

#endif
