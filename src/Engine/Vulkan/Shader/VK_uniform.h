#ifndef VK_UNIFORM_H
#define VK_UNIFORM_H

#include "../Struct/struct_uniform.h"
#include "../Struct/struct_pipeline.h"
#include "../../../common.h"

class Engine;
class Param_vulkan;
class VK_buffer;


class VK_uniform
{
public:
  //Constructor / Destructor
  VK_uniform(Engine* engineManager);
  ~VK_uniform();

public:
  //Main functions
  void create_uniform_buffers(Struct_pipeline* pipeline);
  Struct_uniform* create_uniform_buffer(string name, string type, int binding);
  void update_uniform_buffer(Struct_pipeline* pipeline, glm::mat4& mvp);
  void clean_uniform(Struct_pipeline* pipeline);

private:
  Param_vulkan* param_vulkan;
  VK_buffer* vk_buffer;
};

#endif
