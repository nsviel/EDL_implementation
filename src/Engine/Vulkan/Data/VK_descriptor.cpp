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
void VK_descriptor::init_descriptor(){
  //---------------------------

  this->create_descriptor_pool();
  //this->create_descriptor_set();

  //---------------------------
}
void VK_descriptor::fill_vec_frame(vector<VkDescriptorSet> descriptor_set){
  vector<Frame*> vec_frame = vk_image->get_vec_frame();
  //---------------------------

  for(int i=0; i<vec_frame.size(); i++){
    Frame* frame = vec_frame[i];
    frame->descriptor_set = descriptor_set[i];
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

//Initialization function
void VK_descriptor::create_descriptor_set(){
  VK_texture* vk_texture = engineManager->get_vk_texture();
  VK_uniform* vk_uniform = engineManager->get_vk_uniform();
  VkDevice device = vk_device->get_device();
  vector<VkBuffer> uniformBuffers = vk_uniform->get_uniformBuffers();
  //---------------------------

  std::vector<VkDescriptorSetLayout> layouts(param_vulkan->max_frame, descriptor_layout);
  VkDescriptorSetAllocateInfo allocInfo{};
  allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
  allocInfo.descriptorPool = descriptor_pool;
  allocInfo.descriptorSetCount = static_cast<uint32_t>(param_vulkan->max_frame);
  allocInfo.pSetLayouts = layouts.data();

  vector<VkDescriptorSet> descriptor_set;
  descriptor_set.resize(param_vulkan->max_frame);
  VkResult result = vkAllocateDescriptorSets(device, &allocInfo, descriptor_set.data());
  if(result != VK_SUCCESS){
    throw std::runtime_error("failed to allocate descriptor sets!");
  }

  //Pour toute les frame, specifier les shader data
  for(size_t i=0; i<param_vulkan->max_frame; i++){
    VkDescriptorBufferInfo bufferInfo{};
    bufferInfo.buffer = uniformBuffers[i];
    bufferInfo.offset = 0;
    bufferInfo.range = sizeof(MVP);

    //MVP matrix to GPU
    VkWriteDescriptorSet descriptor_write{};
    descriptor_write.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    descriptor_write.dstSet = descriptor_set[i];
    descriptor_write.dstBinding = 0;
    descriptor_write.dstArrayElement = 0;
    descriptor_write.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    descriptor_write.descriptorCount = 1;
    descriptor_write.pBufferInfo = &bufferInfo;

    vkUpdateDescriptorSets(device, 1, &descriptor_write, 0, nullptr);
  }

  this->fill_vec_frame(descriptor_set);

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

  //Combination and info
  std::array<VkDescriptorSetLayoutBinding, 1> bindings = {layout_ubo};
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
  std::array<VkDescriptorPoolSize, 1> pool_size{};
  pool_size[0].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
  pool_size[0].descriptorCount = static_cast<uint32_t>(param_vulkan->max_frame);

  VkDescriptorPoolCreateInfo pool_info{};
  pool_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
  pool_info.poolSizeCount = static_cast<uint32_t>(pool_size.size());
  pool_info.pPoolSizes = pool_size.data();
  pool_info.maxSets = static_cast<uint32_t>(param_vulkan->max_frame);

  VkResult result = vkCreateDescriptorPool(device, &pool_info, nullptr, &descriptor_pool);
  if(result != VK_SUCCESS){
    throw std::runtime_error("failed to create descriptor pool!");
  }

  //---------------------------
}

//update function
void VK_descriptor::update_descriptor_set(){
  VK_texture* vk_texture = engineManager->get_vk_texture();
  VK_uniform* vk_uniform = engineManager->get_vk_uniform();
  VkDevice device = vk_device->get_device();
  vector<VkBuffer> uniformBuffers = vk_uniform->get_uniformBuffers();
  //---------------------------

  std::vector<VkDescriptorSetLayout> layouts(param_vulkan->max_frame, descriptor_layout);
  VkDescriptorSetAllocateInfo allocInfo{};
  allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
  allocInfo.descriptorPool = descriptor_pool;
  allocInfo.descriptorSetCount = static_cast<uint32_t>(param_vulkan->max_frame);
  allocInfo.pSetLayouts = layouts.data();

  vector<VkDescriptorSet> descriptor_set;
  descriptor_set.resize(param_vulkan->max_frame);
  VkResult result = vkAllocateDescriptorSets(device, &allocInfo, descriptor_set.data());
  if(result != VK_SUCCESS){
    throw std::runtime_error("failed to allocate descriptor sets!");
  }

  //Pour toute les frame, specifier les shader data
  for(size_t i=0; i<param_vulkan->max_frame; i++){
    VkDescriptorBufferInfo bufferInfo{};
    bufferInfo.buffer = uniformBuffers[i];
    bufferInfo.offset = 0;
    bufferInfo.range = sizeof(MVP);

    //MVP matrix to GPU
    VkWriteDescriptorSet descriptor_write{};
    descriptor_write.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    descriptor_write.dstSet = descriptor_set[i];
    descriptor_write.dstBinding = 0;
    descriptor_write.dstArrayElement = 0;
    descriptor_write.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    descriptor_write.descriptorCount = 1;
    descriptor_write.pBufferInfo = &bufferInfo;

    vkUpdateDescriptorSets(device, 1, &descriptor_write, 0, nullptr);
  }

  this->fill_vec_frame(descriptor_set);

  //---------------------------
}
void VK_descriptor::update_descriptor_set_texture(Object* object){
  VK_texture* vk_texture = engineManager->get_vk_texture();
  VK_uniform* vk_uniform = engineManager->get_vk_uniform();
  VkDevice device = vk_device->get_device();
  vector<VkBuffer> uniformBuffers = vk_uniform->get_uniformBuffers();
  //---------------------------

  std::vector<VkDescriptorSetLayout> layouts(param_vulkan->max_frame, descriptor_layout);
  VkDescriptorSetAllocateInfo allocInfo{};
  allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
  allocInfo.descriptorPool = descriptor_pool;
  allocInfo.descriptorSetCount = static_cast<uint32_t>(param_vulkan->max_frame);
  allocInfo.pSetLayouts = layouts.data();

  vector<VkDescriptorSet> descriptor_set;
  descriptor_set.resize(param_vulkan->max_frame);
  VkResult result = vkAllocateDescriptorSets(device, &allocInfo, descriptor_set.data());
  if(result != VK_SUCCESS){
    throw std::runtime_error("failed to allocate descriptor sets!");
  }

  Struct_texture texture = *next(object->list_texture.begin(), 0);

  //Pour toute les frame, specifier les shader data
  for(size_t i=0; i<param_vulkan->max_frame; i++){
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
    descriptor_write[1].pImageInfo = &texture.imageInfo;

    vkUpdateDescriptorSets(device, static_cast<uint32_t>(descriptor_write.size()), descriptor_write.data(), 0, nullptr);
  }

  this->fill_vec_frame(descriptor_set);

  //---------------------------
}
