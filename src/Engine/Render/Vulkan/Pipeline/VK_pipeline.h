#ifndef VK_PIPELINE_H
#define VK_PIPELINE_H

#include "../Struct/struct_pipeline.h"
#include "../Struct/struct_renderpass.h"
#include "../../Core_common.h"

class VK_engine;
class VK_param;
class VK_descriptor;
class VK_viewport;
class VK_shader;
class VK_data;
class VK_binding;


class VK_pipeline
{
public:
  //Constructor / Destructor
  VK_pipeline(VK_engine* vk_engine);
  ~VK_pipeline();

public:
  //Main functions
  void clean_pipeline(Struct_renderpass* renderpass);

  //Pipeline creation
  void create_pipelines(Struct_renderpass* renderpass);
  void create_pipeline_graphics(Struct_pipeline* pipeline, Struct_renderpass* renderpass);
  void create_pipeline_ui(Struct_pipeline* pipeline, Struct_renderpass* renderpass);
  void create_pipeline_layout(Struct_pipeline* pipeline);

  //Pipeline element
  void create_dynamic_state(Struct_pipeline* pipeline);
  void create_viewport(Struct_pipeline* pipeline);
  void create_raster(Struct_pipeline* pipeline);
  void create_multisampling(Struct_pipeline* pipeline);
  void create_depth(Struct_pipeline* pipeline);
  void create_color_blending_state(Struct_pipeline* pipeline);
  void create_color_blending(Struct_pipeline* pipeline);
  void create_topology(Struct_pipeline* pipeline);

  //Subfunction
  void check_struct_pipeline_input(Struct_pipeline* pipeline);
  Struct_pipeline* get_pipeline_byName(Struct_renderpass* renderpass, string name);

private:
  VK_engine* vk_engine;
  VK_param* vk_param;
  VK_descriptor* vk_descriptor;
  VK_viewport* vk_viewport;
  VK_shader* vk_shader;
  VK_data* vk_data;
  VK_binding* vk_binding;
};

#endif
