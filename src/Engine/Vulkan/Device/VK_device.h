#ifndef VK_DEVICE_H
#define VK_DEVICE_H

#include "../Struct/struct_queue.h"
#include "../Struct/struct_swapchain.h"
#include "../../../common.h"

class Node_engine;
class Engine;
class VK_window;
class VK_instance;
class VK_physical_device;

//List of required device extensions
const std::vector<const char*> required_extensions = {
  VK_KHR_SWAPCHAIN_EXTENSION_NAME
};


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
  Engine* engineManager;
  VK_window* vk_window;
  VK_instance* vk_instance;
  VK_physical_device* vk_physical_device;

  VkDevice device;
  VkQueue queue_graphics;
  VkQueue queue_presentation;
};

#endif
