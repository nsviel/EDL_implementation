#ifndef VK_SHADER_H
#define VK_SHADER_H

#include "../Struct/struct_pipeline.h"
#include "../../../common.h"

class VK_engine;
class VK_param;
class VK_device;


class VK_shader
{
public:
  //Constructor / Destructor
  VK_shader(VK_engine* vk_engine);
  ~VK_shader();

public:
  //Main function
  void create_pipeline_shader(Struct_pipeline* pipeline);
  void create_pipeline_shader_module(Struct_pipeline* pipeline);
  void create_pipeline_shader_info(Struct_pipeline* pipeline);

  //Subfunction
  VkShaderModule create_shader_module(const std::vector<char>& code);
  std::vector<char> read_file(const std::string& filename);

private:
  VK_param* vk_param;
  VK_device* vk_device;
};

#endif
