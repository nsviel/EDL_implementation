#include "VK_uniform.h"

#include "../VK_engine.h"
#include "../VK_param.h"
#include "../Data/VK_buffer.h"


//Constructor / Destructor
VK_uniform::VK_uniform(VK_engine* vk_engine){
  //---------------------------

  this->vk_param = vk_engine->get_vk_param();
  this->vk_buffer = vk_engine->get_vk_buffer();

  //---------------------------
}
VK_uniform::~VK_uniform(){}

//Main function
void VK_uniform::create_uniform_buffers(vec_nameTypeBindingTypeStage vec_required, vector<Struct_uniform*>& vec_uniform){
  //---------------------------

  for(int i=0; i<vec_required.size(); i++){
    string name = get<0>(vec_required[i]);
    string type = get<1>(vec_required[i]);
    int binding = get<2>(vec_required[i]);
    VkDescriptorType ubo_type = get<3>(vec_required[i]);

    if(ubo_type == TYPE_UNIFORM){
      Struct_uniform* uniform = create_uniform_buffer(name, type, binding);
      vec_uniform.push_back(uniform);
    }
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
    vkMapMemory(vk_param->device.device, uniform->mem, 0, type_size, 0, &uniform->mapped);

  //---------------------------
  return uniform;
}
void VK_uniform::update_uniform_buffer(Struct_pipeline* pipeline, glm::mat4& mvp){
  //---------------------------

  Struct_uniform* uniform = pipeline->binding.vec_uniform[0];
  memcpy(uniform->mapped, &mvp, sizeof(mvp));

  //---------------------------
}
void VK_uniform::update_uniform_mat4(string uniform_name, Struct_binding& binding, glm::mat4& value){
  bool has_been_found = false;
  //---------------------------

  for(int i=0; i<binding.vec_uniform.size(); i++){
    Struct_uniform* uniform = binding.vec_uniform[i];
    if(uniform->name == uniform_name){
      memcpy(uniform->mapped, &value, sizeof(value));
      has_been_found = true;
      break;
    }
  }

  if(has_been_found == false){
    cout<<"[error] Uniform name not recognized "<<uniform_name<<endl;
  }

  //---------------------------
}
void VK_uniform::clean_uniform(Struct_binding& binding){
  //---------------------------

  for(int i=0; i<binding.vec_uniform.size(); i++){
    Struct_uniform* uniform = binding.vec_uniform[i];
    vkDestroyBuffer(vk_param->device.device, uniform->buffer, nullptr);
    vkFreeMemory(vk_param->device.device, uniform->mem, nullptr);
  }

  //---------------------------
}
