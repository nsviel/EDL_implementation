#ifndef VK_BINDING_H
#define VK_BINDING_H

#include "../../Struct/struct_binding.h"
#include "../../Struct/struct_pipeline.h"
#include "../../Struct/struct_data.h"
#include "../../../../common.h"

class VK_engine;
class VK_param;
class VK_descriptor;
class VK_uniform;
class VK_sampler;


class VK_binding
{
public:
  //Constructor / Destructor
  VK_binding(VK_engine* vk_engine);
  ~VK_binding();

public:
  //Main functions
  void create_pipeline_binding(Struct_pipeline* pipeline);
  void clean_binding(Struct_binding* binding);

  void update_uniform(Struct_binding* binding, mat4 mvp);

  inline VK_uniform* get_vk_uniform(){return vk_uniform;}

private:
  VK_param* vk_param;
  VK_uniform* vk_uniform;
  VK_descriptor* vk_descriptor;
  VK_sampler* vk_sampler;
};

#endif
