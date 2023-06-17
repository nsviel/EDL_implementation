#ifndef VK_RENDERPASS_H
#define VK_RENDERPASS_H

#include "../../Struct/struct_renderpass.h"
#include "../../Struct/struct_pipeline.h"
#include "../../../../common.h"

class VK_engine;
class VK_param;
class VK_color;
class VK_pipeline;
class VK_subpass;

class RP_scene;
class RP_render;
class RP_ui;


class VK_renderpass
{
public:
  //Constructor / Destructor
  VK_renderpass(VK_engine* vk_engine);
  ~VK_renderpass();

public:
  //Main functions
  void init_renderpass();
  void clean_renderpass();
  void clean_renderpass_object(Struct_renderpass* renderpass);

  //Subfunction
  void create_renderpass(Struct_renderpass* renderpass);
  void create_renderpass_obj(Struct_renderpass* renderpass);

private:
  VK_engine* vk_engine;
  VK_param* vk_param;
  VK_color* vk_color;
  VK_pipeline* vk_pipeline;
  VK_subpass* vk_subpass;

  RP_scene* rp_scene;
  RP_render* rp_render;
  RP_ui* rp_ui;
};

#endif
