#ifndef VK_SCENE_H
#define VK_SCENE_H

#include "../../Struct/struct_renderpass.h"
#include "../../Struct/struct_pipeline.h"
#include "../../../../common.h"

class VK_engine;
class VK_param;
class VK_pipeline;
class VK_subpass;


class VK_scene
{
public:
  //Constructor / Destructor
  VK_scene(VK_engine* vk_engine);
  ~VK_scene();

public:
  //Main functions
  void init_renderpass_scene(Struct_renderpass* renderpass);

  //Subpass
  void create_subpass(Struct_renderpass* renderpass);

  //Pipeline
  void create_pipeline_point(Struct_renderpass* renderpass);
  void create_pipeline_line(Struct_renderpass* renderpass);
  void create_pipeline_edl(Struct_renderpass* renderpass);

private:
  VK_engine* vk_engine;
  VK_param* vk_param;
  VK_pipeline* vk_pipeline;
  VK_subpass* vk_subpass;
};

#endif
