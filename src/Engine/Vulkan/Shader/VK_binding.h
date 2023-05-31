#ifndef VK_BINDING_H
#define VK_BINDING_H

#include "../Struct/struct_binding.h"
#include "../Struct/struct_pipeline.h"
#include "../../../common.h"

class Engine;
class Param_vulkan;
class VK_descriptor;
class VK_uniform;


class VK_binding
{
public:
  //Constructor / Destructor
  VK_binding(Engine* engineManager);
  ~VK_binding();

public:
  //Main functions
  void fill_binding_from_requirement(Struct_binding& binding);
  void fill_pipeline_binding(vector<Struct_pipeline*>& vec_pipeline);

private:
  Param_vulkan* param_vulkan;
  VK_uniform* vk_uniform;
  VK_descriptor* vk_descriptor;
};

#endif
