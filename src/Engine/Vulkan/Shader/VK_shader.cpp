#include "VK_shader.h"

#include "../Engine.h"
#include "../Param_vulkan.h"
#include "../Device/VK_device.h"


//Constructor / Destructor
VK_shader::VK_shader(Engine* engineManager){
  //---------------------------

  this->vk_device = engineManager->get_vk_device();
  this->param_vulkan = engineManager->get_param_vulkan();

  //---------------------------
}
VK_shader::~VK_shader(){}

//Main function
void VK_shader::init_shader_module(bool has_compile){
  //---------------------------

  //Compile shader from GLSL to SPIR-V
  if(has_compile){
    int result = system("../src/Engine/Shader/compile.sh");
  }

  //Load spir format shaders
  auto code_vert = read_file(param_vulkan->path_shader_vs);
  auto code_frag = read_file(param_vulkan->path_shader_fs);

  //Create associated shader modules
  this->module_vert = create_shader_module(code_vert);
  this->module_frag = create_shader_module(code_frag);

  //---------------------------
}

//Subfunction
vector<VkPipelineShaderStageCreateInfo> VK_shader::pipeline_shader_info(VkShaderModule module_vert, VkShaderModule module_frag){
  //---------------------------

  //Vertex shader link in pipeline
  VkPipelineShaderStageCreateInfo info_vert{};
  info_vert.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
  info_vert.stage = VK_SHADER_STAGE_VERTEX_BIT;
  info_vert.module = module_vert;
  info_vert.pName = "main";
  info_vert.pSpecializationInfo = nullptr;

  //Fragment shader link in pipeline
  VkPipelineShaderStageCreateInfo info_frag{};
  info_frag.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
  info_frag.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
  info_frag.module = module_frag;
  info_frag.pName = "main";
  info_frag.pSpecializationInfo = nullptr;

  //Shader info array
  vector<VkPipelineShaderStageCreateInfo> shader_stage;
  shader_stage.push_back(info_vert);
  shader_stage.push_back(info_frag);

  //---------------------------
  return shader_stage;
}
VkShaderModule VK_shader::create_shader_module(const std::vector<char>& code){
  //Shader modules are just a thin wrapper around the shader bytecode
  //---------------------------

  //Shader module info
  VkShaderModuleCreateInfo createInfo{};
  createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
  createInfo.codeSize = code.size();
  createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());

  //Shader module creation
  VkShaderModule shaderModule;
  VkResult result = vkCreateShaderModule(param_vulkan->device, &createInfo, nullptr, &shaderModule);
  if (result != VK_SUCCESS) {
    throw std::runtime_error("[error] failed to create shader module!");
  }

  //---------------------------
  return shaderModule;
}
std::vector<char> VK_shader::read_file(const std::string& filename){
  std::ifstream file(filename, std::ios::ate | std::ios::binary);
  //---------------------------

  if (!file.is_open()) {
    throw std::runtime_error("[error] failed to open file!");
  }

  size_t fileSize = (size_t) file.tellg();
  std::vector<char> buffer(fileSize);

  file.seekg(0);
  file.read(buffer.data(), fileSize);

  file.close();

  //---------------------------
  return buffer;
}
