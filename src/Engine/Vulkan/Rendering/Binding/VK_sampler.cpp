#include "VK_sampler.h"

#include "../../VK_engine.h"
#include "../../VK_param.h"
#include "../../Data/VK_buffer.h"


//Constructor / Destructor
VK_sampler::VK_sampler(VK_engine* vk_engine){
  //---------------------------

  this->vk_param = vk_engine->get_vk_param();
  this->vk_buffer = vk_engine->get_vk_buffer();

  //---------------------------
}
VK_sampler::~VK_sampler(){}

//Main function
void VK_sampler::create_sampler(Struct_binding* binding){
  //---------------------------

  vec_descriptor_required& vec_required = binding->vec_required_binding;
  vector<Struct_sampler*>& vec_sampler = binding->vec_sampler;

  for(int i=0; i<vec_required.size(); i++){
    descriptor_required& descriptor = vec_required[i];
    string name = get<0>(descriptor);
    int binding = get<2>(descriptor);
    VkDescriptorType ubo_type = get<3>(descriptor);

    if(ubo_type == TYPE_SAMPLER || ubo_type == VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT){
      Struct_sampler* sampler = create_sampler_obj(name, binding);
      vec_sampler.push_back(sampler);
    }
  }

  //---------------------------
}
Struct_sampler* VK_sampler::create_sampler_obj(string name, int binding){
  Struct_sampler* sampler = new Struct_sampler();
  //---------------------------

  sampler->name = name;
  sampler->binding = binding;

  //---------------------------
  return sampler;
}
