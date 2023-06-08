#ifndef VK_DRAWING_H
#define VK_DRAWING_H

#include "../../Struct/struct_frame.h"
#include "../../Struct/struct_renderpass.h"
#include "../../Struct/struct_command.h"
#include "../../../../common.h"

class VK_engine;
class VK_param;
class VK_window;
class VK_swapchain;
class VK_command;
class VK_cmd;
class VK_descriptor;
class VK_submit;


class VK_drawing
{
public:
  //Constructor / Destructor
  VK_drawing(VK_engine* vk_engine);
  ~VK_drawing();

public:
  //Main functions
  void draw_frame();
  void draw_scene(Struct_renderpass* renderpass);
  void draw_gui(Struct_renderpass* renderpass);
  void draw_canvas(Struct_renderpass* renderpass);

  //Drawing function
  void acquire_next_image(Struct_renderpass* renderpass);
  void submit_command(Struct_submit_command* command);
  void submit_command(Struct_renderpass* renderpass);
  void submit_commands(vector<Struct_renderpass*> vec_renderpass);
  void submit_presentation(Struct_renderpass* renderpass);
  void set_next_frame_ID(Struct_renderpass* renderpass);

private:
  VK_engine* vk_engine;
  VK_param* vk_param;
  VK_window* vk_window;
  VK_swapchain* vk_swapchain;
  VK_command* vk_command;
  VK_cmd* vk_cmd;
  VK_descriptor* vk_descriptor;
  VK_submit* vk_submit;

  vector<Struct_renderpass*> vec_renderpass;
};

#endif
