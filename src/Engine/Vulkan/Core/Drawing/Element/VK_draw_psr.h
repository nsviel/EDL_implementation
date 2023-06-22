#ifndef VK_DRAW_PSR_H
#define VK_DRAW_PSR_H

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
class VK_viewport;


class VK_draw_psr
{
public:
  //Constructor / Destructor
  VK_draw_psr(VK_engine* vk_engine);
  ~VK_draw_psr();

public:
  //Main functions
  void draw_psr(Struct_renderpass* renderpass);
  void cmd_record_psr(Struct_renderpass* renderpass);
  void cmd_viewport(Struct_renderpass* renderpass, VkViewport viewport);
  void cmd_draw_psr(Struct_renderpass* renderpass);

private:
  Timer timer;

  VK_engine* vk_engine;
  VK_param* vk_param;
  VK_command* vk_command;
  VK_cmd* vk_cmd;
  VK_descriptor* vk_descriptor;
  VK_submit* vk_submit;
  VK_viewport* vk_viewport;

};

#endif
