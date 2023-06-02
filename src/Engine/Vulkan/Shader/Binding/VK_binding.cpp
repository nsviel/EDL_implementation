#include "VK_binding.h"
#include "VK_uniform.h"
#include "VK_sampler.h"

#include "../Descriptor/VK_descriptor.h"

#include "../../VK_engine.h"
#include "../../VK_param.h"


//Constructor / Destructor
VK_binding::VK_binding(VK_engine* vk_engine){
  //---------------------------

  this->vk_param = vk_engine->get_vk_param();
  this->vk_descriptor = vk_engine->get_vk_descriptor();
  this->vk_uniform = new VK_uniform(vk_engine);
  this->vk_sampler = new VK_sampler(vk_engine);

  //---------------------------
}
VK_binding::~VK_binding(){}

//Main function
void VK_binding::fill_binding_from_requirement(Struct_binding& binding){
  //---------------------------

  if(binding.vec_required_binding.size() == 0){
    cout<<"[error] no requirement for binding"<<endl;
    exit(0);
  }

  vk_descriptor->create_layout_from_required(binding);
  vk_uniform->create_uniform_buffers(binding);
  vk_sampler->create_sampler(binding);
  vk_descriptor->allocate_descriptor_set(binding);
  vk_descriptor->update_descriptor_set(binding);

  //---------------------------
}
void VK_binding::fill_pipeline_binding(Struct_pipeline* pipeline){
  //---------------------------

  vk_uniform->create_uniform_buffers(pipeline->binding);
  vk_sampler->create_sampler(pipeline->binding);
  vk_descriptor->allocate_descriptor_set(pipeline->binding);
  vk_descriptor->update_descriptor_set(pipeline->binding);

  //---------------------------
}
void VK_binding::clean_binding(Struct_binding& binding){
  //---------------------------

  vkDestroyDescriptorSetLayout(vk_param->device.device, binding.descriptor.layout, nullptr);
  vk_uniform->clean_uniform(binding);

  //---------------------------
}

void VK_binding::update_uniform(Struct_data* data){
  //---------------------------

  vk_uniform->update_uniform_mat4("mvp", data->binding, data->object->mvp);

  //---------------------------
}
