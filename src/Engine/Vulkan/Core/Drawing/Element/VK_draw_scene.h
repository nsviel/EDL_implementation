#ifndef VK_DRAW_SCENE_H
#define VK_DRAW_SCENE_H

#include "../../../Struct/struct_frame.h"
#include "../../../Struct/struct_renderpass.h"
#include "../../../Struct/struct_command.h"
#include "../../../../../common.h"

class VK_engine;
class VK_param;
class VK_command;
class VK_cmd;
class VK_descriptor;
class VK_submit;
class VK_data;
class VK_uniform;
class VK_camera;


class VK_draw_scene
{
public:
  //Constructor / Destructor
  VK_draw_scene(VK_engine* vk_engine);
  ~VK_draw_scene();

public:
  //Main functions
  void draw_scene(Struct_renderpass* renderpass);

  //Subfunction
  void record_command(Struct_renderpass* renderpass);
  void submit_command(Struct_renderpass* renderpass);

  //Command function
  void cmd_draw_scene(Struct_renderpass* renderpass);
  void cmd_draw_glyph(Struct_renderpass* renderpass);

private:
  Timer timer;

  VK_engine* vk_engine;
  VK_param* vk_param;
  VK_command* vk_command;
  VK_cmd* vk_cmd;
  VK_descriptor* vk_descriptor;
  VK_submit* vk_submit;
  VK_data* vk_data;
  VK_uniform* vk_uniform;
  VK_camera* vk_camera;
};

#endif
