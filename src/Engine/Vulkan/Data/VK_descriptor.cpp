#include "VK_descriptor.h"

#include "../Engine.h"
#include "../Param_vulkan.h"
#include "../Shader/VK_uniform.h"
#include "../Data/VK_texture.h"
#include "../Data/VK_buffer.h"
#include "../Device/VK_device.h"
#include "../Swapchain/VK_image.h"

//A descriptor set contains a descriptor set layout and a descriptor pool


//Constructor / Destructor
VK_descriptor::VK_descriptor(Engine* engineManager){
  //---------------------------

  this->engineManager = engineManager;
  this->param_vulkan = engineManager->get_param_vulkan();
  this->vk_device = engineManager->get_vk_device();
  this->vk_image = engineManager->get_vk_image();

  //---------------------------
}
VK_descriptor::~VK_descriptor(){}

//Main function
void VK_descriptor::init_descriptor(Frame* frame){
  //---------------------------




  //---------------------------
}
void VK_descriptor::cleanup(){
  //---------------------------

  vkDestroyDescriptorPool(param_vulkan->device, descriptor_pool, nullptr);
  vkDestroyDescriptorSetLayout(param_vulkan->device, descriptor_layout, nullptr);

  //---------------------------
}

//Descriptor set
void VK_descriptor::allocate_descriptor_set(){
  VK_texture* vk_texture = engineManager->get_vk_texture();
  VK_uniform* vk_uniform = engineManager->get_vk_uniform();
  vector<VkBuffer> uniformBuffers = vk_uniform->get_uniformBuffers();
  //---------------------------

  vector<VkDescriptorSetLayout> layouts(param_vulkan->max_frame, descriptor_layout);
  VkDescriptorSetAllocateInfo allocInfo{};
  allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
  allocInfo.descriptorPool = descriptor_pool;
  allocInfo.descriptorSetCount = static_cast<uint32_t>(param_vulkan->max_frame);
  allocInfo.pSetLayouts = layouts.data();

  vec_descriptor_set.resize(param_vulkan->max_frame);
  VkResult result = vkAllocateDescriptorSets(param_vulkan->device, &allocInfo, vec_descriptor_set.data());
  if(result != VK_SUCCESS){
    throw std::runtime_error("failed to allocate descriptor sets!");
  }

  //Pour toute les frame, specifier les shader data
  //this->update_descriptor_set();

  vector<Frame*> vec_frame = vk_image->get_vec_frame();
  for(int i=0; i<vec_frame.size(); i++){
    Frame* frame = vec_frame[i];
    frame->descriptor_set = vec_descriptor_set[i];
  }

  //---------------------------
}
void VK_descriptor::update_descriptor_set(){
  VK_uniform* vk_uniform = engineManager->get_vk_uniform();
  vector<VkBuffer> uniformBuffers = vk_uniform->get_uniformBuffers();
  //---------------------------

  for(size_t i=0; i<param_vulkan->max_frame; i++){
    VkDescriptorBufferInfo bufferInfo{};
    bufferInfo.buffer = uniformBuffers[i];
    bufferInfo.offset = 0;
    bufferInfo.range = sizeof(MVP);

    //MVP matrix to GPU
    VkWriteDescriptorSet descriptor_write{};
    descriptor_write.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    descriptor_write.dstSet = vec_descriptor_set[i];
    descriptor_write.dstBinding = 0;
    descriptor_write.dstArrayElement = 0;
    descriptor_write.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    descriptor_write.descriptorCount = 1;
    descriptor_write.pBufferInfo = &bufferInfo;

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

    vkUpdateDescriptorSets(param_vulkan->device, 1, &descriptor_write, 0, nullptr);
  }

  //---------------------------
}

//Descriptor layout
void VK_descriptor::create_descriptor_layout(){
  //---------------------------

  vector<VkDescriptorSetLayoutBinding> vec_binding;
  vec_binding.push_back(add_descriptor_binding(uniform, stage_vs, 1, 0));
  vec_binding.push_back(add_descriptor_binding(sampler, stage_fs, 1, 2));

  //Combination and info
  VkDescriptorSetLayoutCreateInfo layoutInfo{};
  layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
  layoutInfo.bindingCount = static_cast<uint32_t>(vec_binding.size());
  layoutInfo.pBindings = vec_binding.data();

  //Descriptor set layout creation
  VkResult result = vkCreateDescriptorSetLayout(param_vulkan->device, &layoutInfo, nullptr, &descriptor_layout);
  if(result != VK_SUCCESS){
    throw std::runtime_error("failed to create descriptor set layout!");
  }

  //---------------------------
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

  //Set descriptor types
  vector<VkDescriptorPoolSize> vec_pool_size;
  vec_pool_size.push_back(add_descriptor_type(uniform, param_vulkan->max_frame));
  vec_pool_size.push_back(add_descriptor_type(sampler, param_vulkan->max_frame));

  VkDescriptorPoolCreateInfo pool_info{};
  pool_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
  pool_info.poolSizeCount = static_cast<uint32_t>(vec_pool_size.size());
  pool_info.pPoolSizes = vec_pool_size.data();
  pool_info.maxSets = static_cast<uint32_t>(param_vulkan->max_frame);

  VkResult result = vkCreateDescriptorPool(param_vulkan->device, &pool_info, nullptr, &descriptor_pool);
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
