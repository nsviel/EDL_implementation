#ifndef RP_UI_H
#define RP_UI_H

#include "../../Struct/struct_renderpass.h"
#include "../../Struct/struct_pipeline.h"
#include "../../../Render_common.h"

class VK_engine;
class VK_param;
class VK_pipeline;
class VK_subpass;
class VK_viewport;


class UI_renderpass
{
public:
  //Constructor / Destructor
  UI_renderpass(VK_engine* vk_engine);
  ~UI_renderpass();

public:
  //Main functions
  void init_renderpass(Struct_renderpass* renderpass);

  //Pipeline
  void create_pipeline_canvas(Struct_renderpass* renderpass);

private:
  VK_engine* vk_engine;
  VK_param* vk_param;
  VK_pipeline* vk_pipeline;
  VK_subpass* vk_subpass;
  VK_viewport* vk_viewport;
};

#endif
