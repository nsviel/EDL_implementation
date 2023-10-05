#ifndef RP_SCENE_H
#define RP_SCENE_H

#include "../../Struct/struct_renderpass.h"
#include "../../Struct/struct_pipeline.h"
#include "../../../Render_common.h"

class VK_engine;
class VK_param;
class VK_pipeline;
class VK_subpass;
class VK_viewport;


class Scene_renderpass
{
public:
  //Constructor / Destructor
  Scene_renderpass(VK_engine* vk_engine);
  ~Scene_renderpass();

public:
  //Main functions
  void init_renderpass(Struct_renderpass* renderpass);

  //Pipeline
  void create_pipeline_point(Struct_renderpass* renderpass);
  void create_pipeline_line(Struct_renderpass* renderpass);

private:
  VK_engine* vk_engine;
  VK_param* vk_param;
  VK_pipeline* vk_pipeline;
  VK_subpass* vk_subpass;
  VK_viewport* vk_viewport;
};

#endif
