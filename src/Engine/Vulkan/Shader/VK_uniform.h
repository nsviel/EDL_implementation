#ifndef VK_UNIFORM_H
#define VK_UNIFORM_H

#include "../Struct/struct_binding.h"
#include "../Struct/struct_pipeline.h"
#include "../../../common.h"

class VK_engine;
class VK_param;
class VK_buffer;


class VK_uniform
{
public:
  //Constructor / Destructor
  VK_uniform(VK_engine* vk_engine);
  ~VK_uniform();

public:
  //Main functions
  void create_uniform_buffers(vec_nameTypeBindingTypeStage vec_required, vector<Struct_uniform*>& vec_uniform);
  Struct_uniform* create_uniform_buffer(string name, string type, int binding);
  void update_uniform_buffer(Struct_pipeline* pipeline, glm::mat4& mvp);
  void update_uniform_mat4(string uniform_name, Struct_binding& binding, glm::mat4& value);
  void clean_uniform(Struct_binding& binding);

private:
  VK_param* vk_param;
  VK_buffer* vk_buffer;
};

#endif
