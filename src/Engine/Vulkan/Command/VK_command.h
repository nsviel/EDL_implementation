#ifndef VK_COMMAND_H
#define VK_COMMAND_H

#include "../../../common.h"

class Engine;
class Param_engine;
class VK_device;
class VK_swapchain;
class VK_renderpass;
class VK_pipeline;
class VK_descriptor;
class VK_viewport;
class VK_window;
class VK_buffer;
class VK_camera;
class VK_physical_device;
class VK_image;


class VK_command
{
public:
  //Constructor / Destructor
  VK_command(Engine* engineManager);
  ~VK_command();

public:
  //Main functions
  void create_command_pool();
  void create_command_buffers();
  void cleanup();

  //Render pass
  void record_command_buffer(VkCommandBuffer command_buffer, uint32_t imageIndex, uint32_t current_frame);
  void compute_render_pass(VkCommandBuffer command_buffer, VkRenderPassBeginInfo renderPassInfo, uint32_t current_frame);

  //Specific commands
  void command_gui(VkCommandBuffer command_buffer);
  void command_drawing_point(VkCommandBuffer command_buffer, uint32_t current_frame);
  void command_drawing_line(VkCommandBuffer command_buffer, uint32_t current_frame);
  void command_viewport(VkCommandBuffer command_buffer);

  //One time command
  VkCommandBuffer command_buffer_begin();
  void command_buffer_end(VkCommandBuffer command_buffer);

  inline std::vector<VkCommandBuffer> get_command_buffer_vec(){return command_buffer_vec;}
  inline VkCommandPool get_command_pool(){return command_pool;}

private:
  Engine* engineManager;
  Param_engine* param_engine;
  VK_device* vk_device;
  VK_swapchain* vk_swapchain;
  VK_renderpass* vk_renderpass;
  VK_pipeline* vk_pipeline;
  VK_descriptor* vk_descriptor;
  VK_viewport* vk_viewport;
  VK_window* vk_window;
  VK_buffer* vk_buffer;
  VK_camera* vk_camera;
  VK_image* vk_image;
  VK_physical_device* vk_physical_device;

  VkCommandPool command_pool;
  std::vector<VkCommandBuffer> command_buffer_vec;
};

#endif
