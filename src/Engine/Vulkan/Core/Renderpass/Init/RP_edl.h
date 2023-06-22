#ifndef RP_EDL_H
#define RP_EDL_H

#include "../../../Struct/struct_renderpass.h"
#include "../../../Struct/struct_pipeline.h"
#include "../../../../Shader/Source/EDL/struct_edl.h"
#include "../../../../../common.h"

class VK_engine;
class VK_param;
class VK_pipeline;
class VK_subpass;


class RP_edl
{
public:
  //Constructor / Destructor
  RP_edl(VK_engine* vk_engine);
  ~RP_edl();

public:
  //Main functions
  void init_renderpass(Struct_renderpass* renderpass);

  //Subpass
  void create_subpass_edl(Struct_renderpass* renderpass);

  //Pipeline
  void create_pipeline_edl(Struct_renderpass* renderpass);

private:
  VK_engine* vk_engine;
  VK_param* vk_param;
  VK_pipeline* vk_pipeline;
  VK_subpass* vk_subpass;
};

#endif
