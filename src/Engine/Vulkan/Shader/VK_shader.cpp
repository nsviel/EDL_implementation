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
void VK_shader::compute_shader_module(Struct_pipeline* pipeline){
  //---------------------------

  //Compile shader from GLSL to SPIR-V
  if(pipeline->compile_shader){
    string vs = pipeline->path_shader_vs;
    string fs = pipeline->path_shader_fs;
    string command = "../src/Engine/Shader/compile.sh " + vs + " " + fs;
    int result = system(command.c_str());
    if(result != 0){
      cout<<"[error] Shader compilation GLSL -> SPIR-V"<<endl;
    }
  }

  //Load spir format shaders
  string path_vs = param_vulkan->path_shader + pipeline->path_shader_vs + ".spv";
  string path_fs = param_vulkan->path_shader + pipeline->path_shader_fs + ".spv";
  auto code_vert = read_file(path_vs);
  auto code_frag = read_file(path_fs);

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
std::vector<char> VK_shader::read_file(const std::string& path){
  std::ifstream file(path, std::ios::ate | std::ios::binary);
  //---------------------------

  if(!file.is_open()){
    throw std::runtime_error("[error] Shader file failed to open " + path);
  }

  size_t fileSize = (size_t) file.tellg();
  std::vector<char> buffer(fileSize);

  file.seekg(0);
  file.read(buffer.data(), fileSize);

  file.close();

  //---------------------------
  return buffer;
}
