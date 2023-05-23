#ifndef VK_SHADER_H
#define VK_SHADER_H

#include "../Struct/struct_pipeline.h"
#include "../../../common.h"

class Engine;
class Param_vulkan;
class VK_device;


class VK_shader
{
public:
  //Constructor / Destructor
  VK_shader(Engine* engineManager);
  ~VK_shader();

public:
  //Main function
  void compute_pipeline_shader(Struct_pipeline* pipeline);
  void compute_pipeline_shader_module(Struct_pipeline* pipeline);
  void compute_pipeline_shader_info(Struct_pipeline* pipeline);

  //Subfunction
  VkShaderModule create_shader_module(const std::vector<char>& code);
  std::vector<char> read_file(const std::string& filename);

private:
  Param_vulkan* param_vulkan;
  VK_device* vk_device;
};

#endif
