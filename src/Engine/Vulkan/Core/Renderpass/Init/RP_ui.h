#ifndef RP_UI_H
#define RP_UI_H

#include "../../../Struct/struct_renderpass.h"
#include "../../../Struct/struct_pipeline.h"
#include "../../../../../common.h"

class VK_engine;
class VK_param;
class VK_pipeline;
class VK_subpass;


class RP_ui
{
public:
  //Constructor / Destructor
  RP_ui(VK_engine* vk_engine);
  ~RP_ui();

public:
  //Main functions
  void init_renderpass_ui(Struct_renderpass* renderpass);

  //Subpass
  void create_subpass(Struct_renderpass* renderpass);

  //Pipeline
  void create_pipeline_triangle(Struct_renderpass* renderpass);

private:
  VK_engine* vk_engine;
  VK_param* vk_param;
  VK_pipeline* vk_pipeline;
  VK_subpass* vk_subpass;
};

#endif
