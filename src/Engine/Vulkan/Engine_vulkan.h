#ifndef ENGINE_VULKAN_H
#define ENGINE_VULKAN_H

#include "VK_struct.h"

#include "../../common.h"

class Node_engine;
class VK_window;
class VK_instance;
class VK_device;
class VK_swapchain;
class VK_renderpass;
class VK_pipeline;
class VK_framebuffer;
class VK_command;
class VK_synchronization;
class VK_drawing;
class VK_buffer;
class VK_descriptor;
class VK_uniform;
class VK_texture;
class VK_depth;


class Engine_vulkan
{
public:
  //Constructor / Destructor
  Engine_vulkan(Node_engine* node_engine);
  ~Engine_vulkan();

public:
  //Main functions
  void init_vulkan();
  void main_loop();
  void clean_vulkan();

  inline VK_device* get_vk_device(){return vk_device;}
  inline VK_framebuffer* get_vk_framebuffer(){return vk_framebuffer;}
  inline VK_window* get_vk_window(){return vk_window;}
  inline VK_swapchain* get_vk_swapchain(){return vk_swapchain;}
  inline VK_synchronization* get_vk_synchronization(){return vk_synchronization;}
  inline VK_command* get_vk_command(){return vk_command;}
  inline VK_instance* get_vk_instance(){return vk_instance;}
  inline VK_renderpass* get_vk_renderpass(){return vk_renderpass;}
  inline VK_pipeline* get_vk_pipeline(){return vk_pipeline;}
  inline VK_buffer* get_vk_buffer(){return vk_buffer;}
  inline VK_descriptor* get_vk_descriptor(){return vk_descriptor;}
  inline VK_uniform* get_vk_uniform(){return vk_uniform;}
  inline VK_texture* get_vk_texture(){return vk_texture;}
  inline VK_depth* get_vk_depth(){return vk_depth;}

private:
  Node_engine* node_engine;
  VK_window* vk_window;
  VK_instance* vk_instance;
  VK_device* vk_device;
  VK_swapchain* vk_swapchain;
  VK_renderpass* vk_renderpass;
  VK_pipeline* vk_pipeline;
  VK_framebuffer* vk_framebuffer;
  VK_command* vk_command;
  VK_synchronization* vk_synchronization;
  VK_drawing* vk_drawing;
  VK_buffer* vk_buffer;
  VK_descriptor* vk_descriptor;
  VK_uniform* vk_uniform;
  VK_depth* vk_depth;
  VK_texture* vk_texture;
};

#endif
