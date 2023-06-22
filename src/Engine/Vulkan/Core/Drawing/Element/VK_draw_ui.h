#ifndef VK_DRAW_UI_H
#define VK_DRAW_UI_H

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


class VK_draw_ui
{
public:
  //Constructor / Destructor
  VK_draw_ui(VK_engine* vk_engine);
  ~VK_draw_ui();

public:
  //Main functions
  void draw_ui(Struct_renderpass* renderpass);

private:
  VK_engine* vk_engine;
  VK_param* vk_param;
  VK_command* vk_command;
  VK_cmd* vk_cmd;
  VK_descriptor* vk_descriptor;
  VK_submit* vk_submit;
  Timer timer;
};

#endif
