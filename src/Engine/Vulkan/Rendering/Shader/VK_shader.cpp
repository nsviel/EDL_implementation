#include "VK_shader.h"

#include "../../VK_engine.h"
#include "../../VK_param.h"
#include "../../Instance/Device/VK_device.h"


//Constructor / Destructor
VK_shader::VK_shader(VK_engine* vk_engine){
  //---------------------------

  this->vk_device = vk_engine->get_vk_device();
  this->vk_param = vk_engine->get_vk_param();

  //---------------------------
}
VK_shader::~VK_shader(){}

//Main function
void VK_shader::create_pipeline_shader(Struct_pipeline* pipeline){
  //---------------------------

  this->create_pipeline_shader_module(pipeline);
  this->create_pipeline_shader_info(pipeline);

  //---------------------------
}

//Subfunction
void VK_shader::create_pipeline_shader_module(Struct_pipeline* pipeline){
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
  string path_vs = vk_param->instance.path_shader + pipeline->path_shader_vs + ".spv";
  string path_fs = vk_param->instance.path_shader + pipeline->path_shader_fs + ".spv";
  auto code_vert = read_file(path_vs);
  auto code_frag = read_file(path_fs);

  //Create associated shader modules
  VkShaderModule module_vert = create_shader_module(code_vert);
  VkShaderModule module_frag = create_shader_module(code_frag);

  pair<VkShaderModule, VkShaderModule> shader_couple;
  shader_couple.first = module_vert;
  shader_couple.second = module_frag;
  pipeline->vec_shader_couple.push_back(shader_couple);

  //---------------------------
}
void VK_shader::create_pipeline_shader_info(Struct_pipeline* pipeline){
  //---------------------------

  pair<VkShaderModule, VkShaderModule>& shader_couple = pipeline->vec_shader_couple[0];

  //Vertex shader link in pipeline
  VkPipelineShaderStageCreateInfo info_vert{};
  info_vert.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
  info_vert.stage = STAGE_VS;
  info_vert.module = shader_couple.first;
  info_vert.pName = "main";
  info_vert.pSpecializationInfo = nullptr;

  //Fragment shader link in pipeline
  VkPipelineShaderStageCreateInfo info_frag{};
  info_frag.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
  info_frag.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
  info_frag.module = shader_couple.second;
  info_frag.pName = "main";
  info_frag.pSpecializationInfo = nullptr;

  //Shader info array
  pipeline->shader_stage.push_back(info_vert);
  pipeline->shader_stage.push_back(info_frag);

  //---------------------------
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
  VkResult result = vkCreateShaderModule(vk_param->device.device, &createInfo, nullptr, &shaderModule);
  if (result != VK_SUCCESS) {
    throw std::runtime_error("[error] failed to create shader module!");
  }

  //---------------------------
  return shaderModule;
}

//Subfunction
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
