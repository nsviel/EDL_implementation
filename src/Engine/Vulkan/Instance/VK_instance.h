#ifndef VK_INSTANCE_H
#define VK_INSTANCE_H

#include "../../../common.h"

class Engine;


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

  //Validation layers
  std::vector<const char*> get_required_extensions();

  inline VkInstance get_instance(){return instance;}

private:
  Engine* engineManager;
  VkInstance instance;
};

#endif
