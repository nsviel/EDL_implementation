#ifndef VK_SAMPLER_H
#define VK_SAMPLER_H

#include "../Struct/struct_binding.h"
#include "../Struct/struct_pipeline.h"
#include "../../Render_common.h"

class VK_engine;
class VK_param;
class VK_buffer;


class VK_sampler
{
public:
  //Constructor / Destructor
  VK_sampler(VK_engine* vk_engine);
  ~VK_sampler();

public:
  //Main functions
  void create_sampler(Struct_binding* binding);
  Struct_sampler* create_sampler_obj(string name, int binding, VkDescriptorType type);

private:
  VK_param* vk_param;
  VK_buffer* vk_buffer;
};

#endif
