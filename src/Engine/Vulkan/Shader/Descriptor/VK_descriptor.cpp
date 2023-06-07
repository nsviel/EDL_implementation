#include "VK_descriptor.h"

#include "../../VK_engine.h"
#include "../../VK_param.h"

//Three steps to create an uniform:
//-create descriptor set layout
//-allocate descriptor set
//-create uniform object
//-update descriptor set
//-update uniform data
//-bind descriptor set


//Constructor / Destructor
VK_descriptor::VK_descriptor(VK_engine* vk_engine){
  //---------------------------

  this->vk_engine = vk_engine;
  this->vk_param = vk_engine->get_vk_param();

  this->pool_nb_descriptor = 1000;
  this->pool_nb_uniform = 1000;
  this->pool_nb_sampler = 100;

  //---------------------------
}
VK_descriptor::~VK_descriptor(){}

//Main function
void VK_descriptor::clean_descriptor_pool(){
  //---------------------------

  vkDestroyDescriptorPool(vk_param->device.device, descriptor_pool, nullptr);

  //---------------------------
}

//Descriptor set allocation
void VK_descriptor::allocate_descriptor_set(vector<VkDescriptorSetLayout>& vec_layout, vector<VkDescriptorSet>& vec_descriptor_set){
  //---------------------------

  VkDescriptorSetAllocateInfo allocation_info{};
  allocation_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
  allocation_info.descriptorPool = descriptor_pool;
  allocation_info.descriptorSetCount = static_cast<uint32_t>(vec_layout.size());
  allocation_info.pSetLayouts = vec_layout.data();

  vec_descriptor_set.resize(vec_layout.size());
  VkResult result = vkAllocateDescriptorSets(vk_param->device.device, &allocation_info, vec_descriptor_set.data());
  if(result != VK_SUCCESS){
    throw std::runtime_error("failed to allocate descriptor sets!");
  }

  //---------------------------
}
void VK_descriptor::allocate_descriptor_set(Struct_binding& binding){
  //---------------------------

  VkDescriptorSetLayout& layout = binding.descriptor.layout;
  VkDescriptorSet& descriptor_set = binding.descriptor.set;

  VkDescriptorSetAllocateInfo allocation_info{};
  allocation_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
  allocation_info.descriptorPool = descriptor_pool;
  allocation_info.descriptorSetCount = 1;
  allocation_info.pSetLayouts = &layout;

  VkResult result = vkAllocateDescriptorSets(vk_param->device.device, &allocation_info, &descriptor_set);
  if(result != VK_SUCCESS){
    throw std::runtime_error("failed to allocate descriptor sets!");
  }

  //---------------------------
}

//Descriptor set update
void VK_descriptor::update_descriptor_set(Struct_binding& binding){
  //---------------------------

  vector<VkWriteDescriptorSet> vec_write_set;

  //Descriptor set write -> uniform
  VkDescriptorBufferInfo descriptor_info;
  VkWriteDescriptorSet write_uniform;
  if(binding.vec_uniform.size() != 0){
    Struct_uniform* uniform = binding.vec_uniform[0];

    descriptor_info = {};
    descriptor_info.buffer = uniform->buffer;
    descriptor_info.offset = 0;
    descriptor_info.range = sizeof(glm::mat4);

    write_uniform = {};
    write_uniform.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    write_uniform.dstSet = binding.descriptor.set;
    write_uniform.dstBinding = 0;
    write_uniform.dstArrayElement = 0;
    write_uniform.descriptorType = TYPE_UNIFORM;
    write_uniform.descriptorCount = 1;
    write_uniform.pBufferInfo = &descriptor_info;
    vec_write_set.push_back(write_uniform);
  }

  //Descriptor set write -> sampler
  VkDescriptorImageInfo image_info;
  VkWriteDescriptorSet write_sampler;
  if(binding.list_texture.size() != 0){
    Struct_image* texture = *next(binding.list_texture.begin(), 0);

    image_info = {};
    image_info.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    image_info.imageView = texture->view;
    image_info.sampler = texture->sampler;

    write_sampler = {};
    write_sampler.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    write_sampler.dstSet = binding.descriptor.set;
    write_sampler.dstBinding = 1;
    write_sampler.dstArrayElement = 0;
    write_sampler.descriptorType = TYPE_SAMPLER;
    write_sampler.descriptorCount = 1;
    write_sampler.pImageInfo = &image_info;
    vec_write_set.push_back(write_sampler);
  }

  vkUpdateDescriptorSets(vk_param->device.device, static_cast<uint32_t>(vec_write_set.size()), vec_write_set.data(), 0, nullptr);

  //---------------------------
}
void VK_descriptor::write_uniform(Struct_binding* binding){
  //---------------------------

  //Descriptor set write -> uniform
  VkDescriptorBufferInfo descriptor_info;
  VkWriteDescriptorSet write_uniform;
  if(binding->vec_uniform.size() != 0){
    Struct_uniform* uniform = binding->vec_uniform[0];

    descriptor_info = {};
    descriptor_info.buffer = uniform->buffer;
    descriptor_info.offset = 0;
    descriptor_info.range = sizeof(glm::mat4);

    write_uniform = {};
    write_uniform.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    write_uniform.dstSet = binding->descriptor.set;
    write_uniform.dstBinding = 0;
    write_uniform.dstArrayElement = 0;
    write_uniform.descriptorType = TYPE_UNIFORM;
    write_uniform.descriptorCount = 1;
    write_uniform.pBufferInfo = &descriptor_info;

    binding->vec_write_set.push_back(write_uniform);
  }

  //---------------------------
}

//Descriptor layout
void VK_descriptor::create_layout_from_required(Struct_binding& binding){
  vec_nameTypeBindingTypeStage& vec_required_binding = binding.vec_required_binding;
  VkDescriptorSetLayout& layout = binding.descriptor.layout;
  //---------------------------

  vector<VkDescriptorSetLayoutBinding> vec_binding;
  for(int i=0; i<vec_required_binding.size(); i++){
    //Get descriptor elements
    VkDescriptorType type = get<3>(vec_required_binding[i]);
    VkShaderStageFlagBits stage = get<4>(vec_required_binding[i]);
    int binding = get<2>(vec_required_binding[i]);

    //Convert it into descriptor binding
    VkDescriptorSetLayoutBinding layout_binding = add_descriptor_binding(type, stage, 1, binding);
    vec_binding.push_back(layout_binding);
  }

  //Create descriptor layout from requirements
  layout = create_layout(vec_binding);

  //---------------------------

}
VkDescriptorSetLayout VK_descriptor::create_layout(vector<VkDescriptorSetLayoutBinding>& vec_binding){
  //---------------------------

  //Combination and info
  VkDescriptorSetLayoutCreateInfo layoutInfo{};
  layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
  layoutInfo.bindingCount = static_cast<uint32_t>(vec_binding.size());
  layoutInfo.pBindings = vec_binding.data();

  //Descriptor set layout creation
  VkDescriptorSetLayout descriptor_layout;
  VkResult result = vkCreateDescriptorSetLayout(vk_param->device.device, &layoutInfo, nullptr, &descriptor_layout);
  if(result != VK_SUCCESS){
    throw std::runtime_error("failed to create descriptor set layout!");
  }

  //---------------------------
  return descriptor_layout;
}
VkDescriptorSetLayoutBinding VK_descriptor::add_descriptor_binding(VkDescriptorType type, VkShaderStageFlagBits stage, int count, int binding){
  //---------------------------

  VkDescriptorSetLayoutBinding layout_binding{};
  layout_binding.binding = binding;
  layout_binding.descriptorCount = static_cast<uint32_t>(count);
  layout_binding.descriptorType = type;
  layout_binding.stageFlags = stage;
  layout_binding.pImmutableSamplers = nullptr; // Optional

  //---------------------------
  return layout_binding;
}

//Descriptor pool
void VK_descriptor::create_descriptor_pool(){
  //---------------------------

  //Maximum number of descriptor per type
  vector<VkDescriptorPoolSize> vec_pool_size;
  vec_pool_size.push_back(add_descriptor_type(TYPE_UNIFORM, pool_nb_uniform));
  vec_pool_size.push_back(add_descriptor_type(TYPE_SAMPLER, pool_nb_sampler));

  VkDescriptorPoolCreateInfo pool_info{};
  pool_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
  pool_info.poolSizeCount = static_cast<uint32_t>(vec_pool_size.size());
  pool_info.pPoolSizes = vec_pool_size.data();
  pool_info.maxSets = static_cast<uint32_t>(pool_nb_descriptor);

  VkResult result = vkCreateDescriptorPool(vk_param->device.device, &pool_info, nullptr, &descriptor_pool);
  if(result != VK_SUCCESS){
    throw std::runtime_error("failed to create descriptor pool!");
  }

  //---------------------------
}
VkDescriptorPoolSize VK_descriptor::add_descriptor_type(VkDescriptorType type, int count){
  //---------------------------

  VkDescriptorPoolSize pool_sampler{};
  pool_sampler.type = type;
  pool_sampler.descriptorCount = static_cast<uint32_t>(count);

  //---------------------------
  return pool_sampler;
}
