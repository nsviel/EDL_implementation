#include "VK_descriptor.h"

#include "../Engine.h"
#include "../Param_vulkan.h"

//Three steps to create an uniform:
//-create descriptor set layout
//-allocate descriptor set
//-create uniform object
//-update descriptor set
//-update uniform data
//-bind descriptor set


//Constructor / Destructor
VK_descriptor::VK_descriptor(Engine* engineManager){
  //---------------------------

  this->engineManager = engineManager;
  this->param_vulkan = engineManager->get_param_vulkan();

  this->pool_nb_descriptor = 1000;
  this->pool_nb_uniform = 1000;
  this->pool_nb_sampler = 1;

  //---------------------------
}
VK_descriptor::~VK_descriptor(){}

//Main function
void VK_descriptor::cleanup(){
  //---------------------------

  vkDestroyDescriptorPool(param_vulkan->device.device, descriptor_pool, nullptr);

  //---------------------------
}

//Descriptor set
void VK_descriptor::allocate_descriptor_set(vector<VkDescriptorSetLayout>& vec_layout, vector<VkDescriptorSet>& vec_descriptor_set){
  //---------------------------

  VkDescriptorSetAllocateInfo allocInfo{};
  allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
  allocInfo.descriptorPool = descriptor_pool;
  allocInfo.descriptorSetCount = static_cast<uint32_t>(vec_layout.size());
  allocInfo.pSetLayouts = vec_layout.data();

  vec_descriptor_set.resize(vec_layout.size());
  VkResult result = vkAllocateDescriptorSets(param_vulkan->device.device, &allocInfo, vec_descriptor_set.data());
  if(result != VK_SUCCESS){
    throw std::runtime_error("failed to allocate descriptor sets!");
  }

  //---------------------------
}
void VK_descriptor::allocate_descriptor_set(VkDescriptorSetLayout& layout, VkDescriptorSet& descriptor_set){
  //---------------------------

  VkDescriptorSetAllocateInfo allocInfo{};
  allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
  allocInfo.descriptorPool = descriptor_pool;
  allocInfo.descriptorSetCount = 1;
  allocInfo.pSetLayouts = &layout;

  VkResult result = vkAllocateDescriptorSets(param_vulkan->device.device, &allocInfo, &descriptor_set);
  if(result != VK_SUCCESS){
    throw std::runtime_error("failed to allocate descriptor sets!");
  }

  //---------------------------
}
void VK_descriptor::update_descriptor_set(Struct_binding& binding){
  //---------------------------

  Struct_uniform* uniform = binding.vec_uniform[0];

  VkDescriptorBufferInfo bufferInfo{};
  bufferInfo.buffer = uniform->buffer;
  bufferInfo.offset = 0;
  bufferInfo.range = sizeof(glm::mat4);

  //MVP matrix to GPU
  VkWriteDescriptorSet descriptor_write{};
  descriptor_write.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
  descriptor_write.dstSet = binding.descriptor.set;
  descriptor_write.dstBinding = uniform->binding;
  descriptor_write.dstArrayElement = 0;
  descriptor_write.descriptorType = TYPE_UNIFORM;
  descriptor_write.descriptorCount = 1;
  descriptor_write.pBufferInfo = &bufferInfo;
  descriptor_write.pImageInfo = nullptr; // Optional
  descriptor_write.pTexelBufferView = nullptr; // Optional

  /*
  //Texture to GPU
  descriptor_write[1].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
  descriptor_write[1].dstSet = vec_descriptor_set[i];
  descriptor_write[1].dstBinding = 1;
  descriptor_write[1].dstArrayElement = 0;
  descriptor_write[1].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
  descriptor_write[1].descriptorCount = 1;
  descriptor_write[1].pImageInfo = &texture.imageInfo;
  */

  vkUpdateDescriptorSets(param_vulkan->device.device, 1, &descriptor_write, 0, nullptr);

  //---------------------------
}

//Descriptor layout
VkDescriptorSetLayout VK_descriptor::create_layout_from_required(vec_nameTypeBindingTypeStage& vec_required_binding){
  //---------------------------

  vector<VkDescriptorSetLayoutBinding> vec_binding;
  for(int i=0; i<vec_required_binding.size(); i++){
    VkDescriptorType type = get<3>(vec_required_binding[i]);
    VkShaderStageFlagBits stage = get<4>(vec_required_binding[i]);
    int binding = get<2>(vec_required_binding[i]);

    VkDescriptorSetLayoutBinding layout_binding = add_descriptor_binding(type, stage, 1, binding);

    vec_binding.push_back(layout_binding);
  }

  //---------------------------
  return create_layout(vec_binding);
}
VkDescriptorSetLayout VK_descriptor::create_layout(vector<VkDescriptorSetLayoutBinding> vec_binding){
  //---------------------------

  //Combination and info
  VkDescriptorSetLayoutCreateInfo layoutInfo{};
  layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
  layoutInfo.bindingCount = static_cast<uint32_t>(vec_binding.size());
  layoutInfo.pBindings = vec_binding.data();

  //Descriptor set layout creation
  VkDescriptorSetLayout descriptor_layout;
  VkResult result = vkCreateDescriptorSetLayout(param_vulkan->device.device, &layoutInfo, nullptr, &descriptor_layout);
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

  VkResult result = vkCreateDescriptorPool(param_vulkan->device.device, &pool_info, nullptr, &descriptor_pool);
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
