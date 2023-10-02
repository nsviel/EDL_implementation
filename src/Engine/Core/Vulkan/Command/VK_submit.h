#ifndef VK_SUBMIT_H
#define VK_SUBMIT_H

#include "../Struct/struct_frame.h"
#include "../Struct/struct_renderpass.h"
#include "../Struct/struct_command.h"
#include "../Struct/struct_swapchain.h"
#include "../../../common.h"

class VK_engine;
class VK_param;
class VK_window;
class VK_swapchain;
class VK_command;
class VK_cmd;
class VK_descriptor;


class VK_submit
{
public:
  //Constructor / Destructor
  VK_submit(VK_engine* vk_engine);
  ~VK_submit();

public:
  //Main functions
  void acquire_next_image(Struct_swapchain* swapchain);
  void set_next_frame_ID(Struct_swapchain* swapchain);
  void set_next_frame_ID(Struct_renderpass* renderpass);

  //Queue submission
  void submit_graphics_command(Struct_submit_command* command);
  void submit_graphics_commands(Struct_submit_commands* commands);
  void submit_presentation(Struct_swapchain* swapchain);

private:
  VK_engine* vk_engine;
  VK_param* vk_param;
  VK_window* vk_window;
  VK_swapchain* vk_swapchain;
  VK_command* vk_command;
  VK_cmd* vk_cmd;
  VK_descriptor* vk_descriptor;

  vector<Struct_renderpass*> vec_renderpass;
};

#endif
