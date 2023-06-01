#ifndef VK_PIPELINE_H
#define VK_PIPELINE_H

#include "../Struct/struct_pipeline.h"
#include "../../../common.h"

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
  void init_pipeline();
  void cleanup();

  //Pipeline creation
  void create_pipeline_info(Struct_pipeline* pipeline);
  void create_pipeline_layout(Struct_pipeline* pipeline);
  void create_pipeline_graphics();

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
  Struct_pipeline* get_pipeline_byName(string name);

private:
  VK_engine* vk_engine;
  VK_param* vk_param;
  VK_descriptor* vk_descriptor;
  VK_viewport* vk_viewport;
  VK_shader* vk_shader;
  VK_data* vk_data;
  VK_binding* vk_binding;

  vector<Struct_pipeline*> vec_pipeline;
};

#endif
