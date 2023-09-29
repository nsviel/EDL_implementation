#include "VK_binding.h"
#include "VK_uniform.h"
#include "VK_sampler.h"

#include "../Binding/VK_descriptor.h"

#include "../../VK_engine.h"
#include "../../VK_param.h"


//Constructor / Destructor
VK_binding::VK_binding(VK_engine* vk_engine){
  //---------------------------

  this->vk_param = vk_engine->get_vk_param();
  this->vk_descriptor = vk_engine->get_vk_descriptor();
  this->vk_uniform = vk_engine->get_vk_uniform();
  this->vk_sampler = new VK_sampler(vk_engine);

  //---------------------------
}
VK_binding::~VK_binding(){}

//Main function
void VK_binding::create_binding(Struct_binding* binding){
  //---------------------------

  vk_uniform->create_uniform_buffers(binding);
  vk_sampler->create_sampler(binding);
  vk_descriptor->allocate_descriptor_set(binding);
  vk_descriptor->update_descriptor_uniform(binding);

  //---------------------------
}
void VK_binding::clean_binding(Struct_binding* binding){
  //---------------------------

  vkDestroyDescriptorSetLayout(vk_param->device.device, binding->descriptor.layout, nullptr);
  vk_uniform->clean_uniform(binding);

  //---------------------------
}

void VK_binding::update_uniform(Struct_binding* binding, mat4 mvp){
  //---------------------------

  vk_uniform->update_uniform_mat4("mvp", binding, mvp);

  //---------------------------
}
