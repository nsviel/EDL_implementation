#include "VK_binding.h"
#include "VK_descriptor.h"
#include "VK_uniform.h"

#include "../Engine.h"
#include "../Param_vulkan.h"


//Constructor / Destructor
VK_binding::VK_binding(Engine* engineManager){
  //---------------------------

  this->param_vulkan = engineManager->get_param_vulkan();
  this->vk_descriptor = engineManager->get_vk_descriptor();
  this->vk_uniform = engineManager->get_vk_uniform();

  //---------------------------
}
VK_binding::~VK_binding(){}

//Main function
void VK_binding::fill_binding_from_requirement(Struct_binding& binding){
  //---------------------------

  binding.descriptor.layout = vk_descriptor->create_layout_from_required(binding.vec_required_binding);
  vk_uniform->create_uniform_buffers(binding.vec_required_binding, binding.vec_uniform);
  vk_descriptor->allocate_descriptor_set(binding.descriptor.layout, binding.descriptor.set);
  vk_descriptor->update_descriptor_set(binding);

  //---------------------------
}
void VK_binding::fill_pipeline_binding(vector<Struct_pipeline*>& vec_pipeline){
  //---------------------------

  //Create uniform buffer and get descriptor layouts
  vector<VkDescriptorSetLayout> vec_layout;
  for(int i=0; i<vec_pipeline.size(); i++){
    Struct_pipeline* pipeline = vec_pipeline[i];
    vec_layout.push_back(pipeline->binding.descriptor.layout);
    vk_uniform->create_uniform_buffers(pipeline->binding.vec_required_binding, pipeline->binding.vec_uniform);
  }

  //Allocate descriptor
  vector<VkDescriptorSet> vec_descriptor_set;
  vk_descriptor->allocate_descriptor_set(vec_layout, vec_descriptor_set);

  //Update descriptor set
  for(int i=0; i<vec_pipeline.size(); i++){
    Struct_pipeline* pipeline = vec_pipeline[i];
    pipeline->binding.descriptor.set = vec_descriptor_set[i];
    vk_descriptor->update_descriptor_set(pipeline->binding);
  }

  //---------------------------
}
