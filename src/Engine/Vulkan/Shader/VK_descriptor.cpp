#include "VK_descriptor.h"

#include "../Engine.h"
#include "../Param_vulkan.h"
#include "../Data/VK_texture.h"
#include "../Data/VK_buffer.h"
#include "../Device/VK_device.h"
#include "../Swapchain/VK_frame.h"

//A descriptor set contains a descriptor set layout and a descriptor pool


//Constructor / Destructor
VK_descriptor::VK_descriptor(Engine* engineManager){
  //---------------------------

  this->engineManager = engineManager;
  this->param_vulkan = engineManager->get_param_vulkan();
  this->vk_device = engineManager->get_vk_device();
  this->vk_frame = engineManager->get_vk_image();
  this->vk_texture = engineManager->get_vk_texture();

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
void VK_descriptor::allocate_descriptor_set(vector<Struct_pipeline*> vec_pipeline){
  //---------------------------

  vector<VkDescriptorSetLayout> vec_layout;
  for(int i=0; i<vec_pipeline.size(); i++){
    Struct_pipeline* pipeline = vec_pipeline[i];
    vec_layout.push_back(pipeline->descriptor_layout);
  }

  VkDescriptorSetAllocateInfo allocInfo{};
  allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
  allocInfo.descriptorPool = descriptor_pool;
  allocInfo.descriptorSetCount = static_cast<uint32_t>(vec_layout.size());
  allocInfo.pSetLayouts = vec_layout.data();

  vector<VkDescriptorSet> vec_descriptor_set;
  vec_descriptor_set.resize(vec_pipeline.size());
  VkResult result = vkAllocateDescriptorSets(param_vulkan->device.device, &allocInfo, vec_descriptor_set.data());
  if(result != VK_SUCCESS){
    throw std::runtime_error("failed to allocate descriptor sets!");
  }

  for(int i=0; i<vec_pipeline.size(); i++){
    Struct_pipeline* pipeline = vec_pipeline[i];
    pipeline->descriptor_set = vec_descriptor_set[i];
    this->configure_descriptor_set(pipeline);
  }

  //---------------------------
}
void VK_descriptor::configure_descriptor_set(Struct_pipeline* pipeline){
  //---------------------------

  Struct_uniform* uniform = pipeline->vec_uniform[0];

  VkDescriptorBufferInfo bufferInfo{};
  bufferInfo.buffer = uniform->buffer;
  bufferInfo.offset = 0;
  bufferInfo.range = sizeof(glm::mat4);

  //MVP matrix to GPU
  VkWriteDescriptorSet descriptor_write{};
  descriptor_write.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
  descriptor_write.dstSet = pipeline->descriptor_set;
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
VkDescriptorSetLayout VK_descriptor::create_layout_scene(){
  //---------------------------

  vector<VkDescriptorSetLayoutBinding> vec_binding;
  vec_binding.push_back(add_descriptor_binding(TYPE_UNIFORM, STAGE_VS, 1, 0));

  //---------------------------
  return create_layout(vec_binding);
}
VkDescriptorSetLayout VK_descriptor::create_layout_glyph(){
  //---------------------------

  vector<VkDescriptorSetLayoutBinding> vec_binding;
  vec_binding.push_back(add_descriptor_binding(TYPE_UNIFORM, STAGE_VS, 1, 0));

  //---------------------------
  return create_layout(vec_binding);
}
VkDescriptorSetLayout VK_descriptor::create_layout_canvas(){
  //---------------------------

  vector<VkDescriptorSetLayoutBinding> vec_binding;
  vec_binding.push_back(add_descriptor_binding(TYPE_UNIFORM, STAGE_VS, 1, 0));
  vec_binding.push_back(add_descriptor_binding(TYPE_SAMPLER, STAGE_FS, 1, 2));

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
  pool_info.maxSets = static_cast<uint32_t>(3);

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
