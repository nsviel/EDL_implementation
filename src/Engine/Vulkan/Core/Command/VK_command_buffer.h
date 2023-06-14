#ifndef VK_COMMAND_BUFFER_H
#define VK_COMMAND_BUFFER_H

#include "../../Struct/struct_renderpass.h"
#include "../../../../common.h"

class VK_engine;
class VK_param;
class VK_physical_device;


class VK_command_buffer
{
public:
  //Constructor / Destructor
  VK_command_buffer(VK_engine* vk_engine);
  ~VK_command_buffer();

public:
  //Command pool
  void create_command_pool();
  void clean_command_pool();

  //Command buffer
  void allocate_command_buffer(Struct_renderpass* renderpass);

  inline VkCommandPool get_command_pool(){return command_pool;}

private:
  VK_engine* vk_engine;
  VK_param* vk_param;
  VK_physical_device* vk_physical_device;

  VkCommandPool command_pool;
};

#endif
