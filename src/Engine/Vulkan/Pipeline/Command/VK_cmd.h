#ifndef VK_CMD_H
#define VK_CMD_H

#include "../../Struct/struct_renderpass.h"
#include "../../../../common.h"

class VK_engine;
class VK_param;
class VK_viewport;
class VK_pipeline;
class VK_camera;
class VK_canvas;
class VK_binding;
class VK_data;


class VK_cmd
{
public:
  //Constructor / Destructor
  VK_cmd(VK_engine* vk_engine);
  ~VK_cmd();

public:
  //Main function
  void cmd_record_scene(Struct_renderpass* renderpass);
  void cmd_record_glyph(Struct_renderpass* renderpass);
  void cmd_record_gui(Struct_renderpass* renderpass);

  //Renderpass command
  void cmd_viewport(Struct_renderpass* renderpass);
  void cmd_drawing_scene(Struct_renderpass* renderpass);
  void cmd_drawing_scene_2(Struct_renderpass* renderpass);
  void cmd_drawing_glyph(Struct_renderpass* renderpass);
  void cmd_drawing_canvas(Struct_renderpass* renderpass);

private:
  VK_engine* vk_engine;
  VK_param* vk_param;
  VK_pipeline* vk_pipeline;
  VK_camera* vk_camera;
  VK_canvas* vk_canvas;
  VK_binding* vk_binding;
  VK_data* vk_data;
  VK_viewport* vk_viewport;
};

#endif
