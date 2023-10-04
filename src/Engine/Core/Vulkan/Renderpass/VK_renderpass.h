#ifndef VK_RENDERPASS_H
#define VK_RENDERPASS_H

#include "../Struct/struct_renderpass.h"
#include "../Struct/struct_pipeline.h"
#include "../../Core_common.h"

class VK_engine;
class VK_param;
class VK_color;
class VK_pipeline;
class VK_subpass;

class Scene_renderpass;
class EDL_renderpas;
class RP_psr;
class UI_renderpass;


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

  Scene_renderpass* rp_scene;
  EDL_renderpas* rp_edl;
  RP_psr* rp_psr;
  UI_renderpass* rp_ui;
};

#endif
