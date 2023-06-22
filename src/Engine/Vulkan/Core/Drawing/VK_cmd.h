#ifndef VK_CMD_H
#define VK_CMD_H

#include "../../Struct/struct_renderpass.h"
#include "../../../../common.h"

class Shader_edl;
class VK_engine;
class VK_param;
class VK_viewport;
class VK_pipeline;
class VK_camera;
class VK_canvas;
class VK_data;
class VK_uniform;
class VK_descriptor;
class VK_command;
class VK_gui;


class VK_cmd
{
public:
  //Constructor / Destructor
  VK_cmd(VK_engine* vk_engine);
  ~VK_cmd();

public:
  //Main function
  void cmd_record_scene(Struct_renderpass* renderpass);
  void cmd_record_edl(Struct_renderpass* renderpass);
  void cmd_record_ui(Struct_renderpass* renderpass);

  //Renderpass command
  void cmd_viewport(Struct_renderpass* renderpass, VkViewport viewport);
  void cmd_draw_scene(Struct_renderpass* renderpass);
  void cmd_draw_glyph(Struct_renderpass* renderpass);
  void cmd_draw_canvas(Struct_renderpass* renderpass);
  void cmd_draw_edl(Struct_renderpass* renderpass);

  //Secondary command buffer
  void cmd_record_scene_secondcb(Struct_renderpass* renderpass);

private:
  Shader_edl* shader_edl;
  VK_engine* vk_engine;
  VK_param* vk_param;
  VK_pipeline* vk_pipeline;
  VK_camera* vk_camera;
  VK_canvas* vk_canvas;
  VK_data* vk_data;
  VK_viewport* vk_viewport;
  VK_uniform* vk_uniform;
  VK_descriptor* vk_descriptor;
  VK_command* vk_command;
  VK_gui* vk_gui;
};

#endif
