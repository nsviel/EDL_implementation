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
  void compute_shader_module(Struct_pipeline* pipeline);

  //Subfunction
  VkShaderModule create_shader_module(const std::vector<char>& code);
  vector<VkPipelineShaderStageCreateInfo> pipeline_shader_info(VkShaderModule module_vert, VkShaderModule module_frag);
  std::vector<char> read_file(const std::string& filename);

  inline VkShaderModule get_module_vert(){return module_vert;}
  inline VkShaderModule get_module_frag(){return module_frag;}

private:
  Param_vulkan* param_vulkan;
  VK_device* vk_device;

  VkShaderModule module_vert;
  VkShaderModule module_frag;
};

#endif
