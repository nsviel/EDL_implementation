#include "VK_uniform.h"

#include "../Engine.h"
#include "../Param_vulkan.h"
#include "../Data/VK_buffer.h"


//Constructor / Destructor
VK_uniform::VK_uniform(Engine* engineManager){
  //---------------------------

  this->param_vulkan = engineManager->get_param_vulkan();
  this->vk_buffer = engineManager->get_vk_buffer();

  //---------------------------
}
VK_uniform::~VK_uniform(){}

//Main function
void VK_uniform::create_uniform_buffers(Struct_pipeline* pipeline){
  //---------------------------

  for(int i=0; i<pipeline->vec_required_uniform.size(); i++){
    name_type_binding info = pipeline->vec_required_uniform[i];
    Struct_uniform* uniform = create_uniform_buffer(get<0>(info), get<1>(info), get<2>(info));
    pipeline->vec_uniform.push_back(uniform);
  }

  //---------------------------
}
Struct_uniform* VK_uniform::create_uniform_buffer(string name, string type, int binding){
  Struct_uniform* uniform = new Struct_uniform();
  //---------------------------

    uniform->name = name;
    uniform->binding = binding;

    std::size_t type_size;
    if(type == "mat4"){
      type_size = sizeof(glm::mat4);
    }else{
      cout<<"[error] Uniform type not recognized"<<endl;
      exit(0);
    }

    vk_buffer->create_gpu_buffer(type_size, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, uniform->buffer);
    vk_buffer->bind_buffer_memory(MEMORY_SHARED_CPU_GPU, uniform->buffer, uniform->mem);
    vkMapMemory(param_vulkan->device.device, uniform->mem, 0, type_size, 0, &uniform->mapped);

  //---------------------------
  return uniform;
}
void VK_uniform::update_uniform_buffer(Struct_pipeline* pipeline, glm::mat4& mvp){
  //---------------------------

  Struct_uniform* uniform = pipeline->vec_uniform[0];
  memcpy(uniform->mapped, &mvp, sizeof(mvp));

  //---------------------------
}
void VK_uniform::clean_uniform(Struct_pipeline* pipeline){
  //---------------------------

  Struct_uniform* uniform = pipeline->vec_uniform[0];

  vkDestroyBuffer(param_vulkan->device.device, uniform->buffer, nullptr);
  vkFreeMemory(param_vulkan->device.device, uniform->mem, nullptr);

  //---------------------------
}
