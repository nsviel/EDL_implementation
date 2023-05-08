#include "VK_descriptor.h"

#include "../Shader/VK_uniform.h"
#include "../VK_parameter.h"
#include "../Engine.h"
#include "../Data/VK_texture.h"
#include "../Data/VK_buffer.h"
#include "../Device/VK_device.h"

//A descriptor set contains a descriptor set layout and a descriptor pool


//Constructor / Destructor
VK_descriptor::VK_descriptor(Engine* engineManager){
  //---------------------------

  this->engineManager = engineManager;
  this->vk_device = engineManager->get_vk_device();

  //---------------------------
}
VK_descriptor::~VK_descriptor(){}

//Main function
void VK_descriptor::init_descriptor(){
  //---------------------------

  this->create_descriptor_pool();
  this->create_descriptor_set();

  //---------------------------
}

//Subfunctions
void VK_descriptor::create_descriptor_set(){
  VK_texture* vk_texture = engineManager->get_vk_texture();
  VK_uniform* vk_uniform = engineManager->get_vk_uniform();
  VkDevice device = vk_device->get_device();
  vector<VkBuffer> uniformBuffers = vk_uniform->get_uniformBuffers();
  //---------------------------

  std::vector<VkDescriptorSetLayout> layouts(MAX_FRAMES_IN_FLIGHT, descriptor_layout);
  VkDescriptorSetAllocateInfo allocInfo{};
  allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
  allocInfo.descriptorPool = descriptor_pool;
  allocInfo.descriptorSetCount = static_cast<uint32_t>(MAX_FRAMES_IN_FLIGHT);
  allocInfo.pSetLayouts = layouts.data();

  descriptor_set.resize(MAX_FRAMES_IN_FLIGHT);
  VkResult result = vkAllocateDescriptorSets(device, &allocInfo, descriptor_set.data());
  if(result != VK_SUCCESS){
    throw std::runtime_error("failed to allocate descriptor sets!");
  }

  //Pour toute les frame, specifier les shader data
  for(size_t i=0; i<MAX_FRAMES_IN_FLIGHT; i++){
    VkDescriptorBufferInfo bufferInfo{};
    bufferInfo.buffer = uniformBuffers[i];
    bufferInfo.offset = 0;
    bufferInfo.range = sizeof(MVP);

    //MVP matrix to GPU
    std::array<VkWriteDescriptorSet, 2> descriptor_write{};
    descriptor_write[0].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    descriptor_write[0].dstSet = descriptor_set[i];
    descriptor_write[0].dstBinding = 0;
    descriptor_write[0].dstArrayElement = 0;
    descriptor_write[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    descriptor_write[0].descriptorCount = 1;
    descriptor_write[0].pBufferInfo = &bufferInfo;

    //Texture to GPU
    descriptor_write[1].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    descriptor_write[1].dstSet = descriptor_set[i];
    descriptor_write[1].dstBinding = 1;
    descriptor_write[1].dstArrayElement = 0;
    descriptor_write[1].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    descriptor_write[1].descriptorCount = 1;
    descriptor_write[1].pImageInfo = 0;

    vkUpdateDescriptorSets(device, static_cast<uint32_t>(descriptor_write.size()), descriptor_write.data(), 0, nullptr);
  }

  //---------------------------
}
void VK_descriptor::create_descriptor_set_layout(){
  VkDevice device = vk_device->get_device();
  //---------------------------

  //Uniform buffer object
  VkDescriptorSetLayoutBinding layout_ubo{};
  layout_ubo.binding = 0;
  layout_ubo.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
  layout_ubo.descriptorCount = 1;
  layout_ubo.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
  layout_ubo.pImmutableSamplers = nullptr; // Optional

  //Sampler
  VkDescriptorSetLayoutBinding layout_sampler{};
  layout_sampler.binding = 1;
  layout_sampler.descriptorCount = 1;
  layout_sampler.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
  layout_sampler.pImmutableSamplers = nullptr;
  layout_sampler.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;

  //Combination and info
  std::array<VkDescriptorSetLayoutBinding, 2> bindings = {layout_ubo, layout_sampler};
  VkDescriptorSetLayoutCreateInfo layoutInfo{};
  layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
  layoutInfo.bindingCount = static_cast<uint32_t>(bindings.size());
  layoutInfo.pBindings = bindings.data();

  //Descriptor set layout creation
  VkResult result = vkCreateDescriptorSetLayout(device, &layoutInfo, nullptr, &descriptor_layout);
  if(result != VK_SUCCESS){
    throw std::runtime_error("failed to create descriptor set layout!");
  }

  //---------------------------
}
void VK_descriptor::create_descriptor_pool(){
  VkDevice device = vk_device->get_device();
  //---------------------------

  //One descriptor per frame
  std::array<VkDescriptorPoolSize, 2> pool_size{};
  pool_size[0].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
  pool_size[0].descriptorCount = static_cast<uint32_t>(MAX_FRAMES_IN_FLIGHT);
  pool_size[1].type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
  pool_size[1].descriptorCount = static_cast<uint32_t>(MAX_FRAMES_IN_FLIGHT);

  VkDescriptorPoolCreateInfo pool_info{};
  pool_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
  pool_info.poolSizeCount = static_cast<uint32_t>(pool_size.size());
  pool_info.pPoolSizes = pool_size.data();
  pool_info.maxSets = static_cast<uint32_t>(MAX_FRAMES_IN_FLIGHT);

  VkResult result = vkCreateDescriptorPool(device, &pool_info, nullptr, &descriptor_pool);
  if(result != VK_SUCCESS){
    throw std::runtime_error("failed to create descriptor pool!");
  }

  //---------------------------
}

void VK_descriptor::update_descriptor_set(Object* object){
  VK_texture* vk_texture = engineManager->get_vk_texture();
  VK_uniform* vk_uniform = engineManager->get_vk_uniform();
  VkDevice device = vk_device->get_device();
  vector<VkBuffer> uniformBuffers = vk_uniform->get_uniformBuffers();
  //---------------------------

  std::vector<VkDescriptorSetLayout> layouts(MAX_FRAMES_IN_FLIGHT, descriptor_layout);
  VkDescriptorSetAllocateInfo allocInfo{};
  allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
  allocInfo.descriptorPool = descriptor_pool;
  allocInfo.descriptorSetCount = static_cast<uint32_t>(MAX_FRAMES_IN_FLIGHT);
  allocInfo.pSetLayouts = layouts.data();

  descriptor_set.resize(MAX_FRAMES_IN_FLIGHT);
  VkResult result = vkAllocateDescriptorSets(device, &allocInfo, descriptor_set.data());
  if(result != VK_SUCCESS){
    throw std::runtime_error("failed to allocate descriptor sets!");
  }

  //Pour toute les frame, specifier les shader data
  for(size_t i=0; i<MAX_FRAMES_IN_FLIGHT; i++){
    VkDescriptorBufferInfo bufferInfo{};
    bufferInfo.buffer = uniformBuffers[i];
    bufferInfo.offset = 0;
    bufferInfo.range = sizeof(MVP);

    //MVP matrix to GPU
    std::array<VkWriteDescriptorSet, 2> descriptor_write{};
    descriptor_write[0].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    descriptor_write[0].dstSet = descriptor_set[i];
    descriptor_write[0].dstBinding = 0;
    descriptor_write[0].dstArrayElement = 0;
    descriptor_write[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    descriptor_write[0].descriptorCount = 1;
    descriptor_write[0].pBufferInfo = &bufferInfo;

    Struct_texture texture = *next(object->list_texture.begin(), 0);

    //Texture to GPU
    descriptor_write[1].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    descriptor_write[1].dstSet = descriptor_set[i];
    descriptor_write[1].dstBinding = 1;
    descriptor_write[1].dstArrayElement = 0;
    descriptor_write[1].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    descriptor_write[1].descriptorCount = 1;
    descriptor_write[1].pImageInfo = &texture.imageInfo;

    vkUpdateDescriptorSets(device, static_cast<uint32_t>(descriptor_write.size()), descriptor_write.data(), 0, nullptr);
  }

  //---------------------------
}
void VK_descriptor::cleanup(){
  VkDevice device = vk_device->get_device();
  //---------------------------

  vkDestroyDescriptorPool(device, descriptor_pool, nullptr);
  vkDestroyDescriptorSetLayout(device, descriptor_layout, nullptr);

  //---------------------------
}
