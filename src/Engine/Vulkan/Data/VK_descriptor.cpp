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
  //---------------------------

  vkDestroyDescriptorPool(param_vulkan->device, descriptor_pool, nullptr);
  vkDestroyDescriptorSetLayout(param_vulkan->device, descriptor_layout, nullptr);

  //---------------------------
}

//Initialization function
void VK_descriptor::create_descriptor_layout(){
  vector<VkDescriptorSetLayoutBinding> vec_layout;
  //---------------------------

  //Uniform buffer object
  VkDescriptorSetLayoutBinding layout_ubo{};
  layout_ubo.binding = 0;
  layout_ubo.descriptorCount = 1;
  layout_ubo.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
  layout_ubo.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
  layout_ubo.pImmutableSamplers = nullptr; // Optional
  vec_layout.push_back(layout_ubo);

  VkDescriptorSetLayoutBinding layout_texture{};
  layout_texture.binding = 2;
  layout_texture.descriptorCount = 1;
  layout_texture.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
  layout_texture.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;
  layout_texture.pImmutableSamplers = nullptr; // Optional
  vec_layout.push_back(layout_texture);

    //Combination and info
  VkDescriptorSetLayoutCreateInfo layoutInfo{};
  layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
  layoutInfo.bindingCount = static_cast<uint32_t>(vec_layout.size());
  layoutInfo.pBindings = vec_layout.data();

  //Descriptor set layout creation
  VkResult result = vkCreateDescriptorSetLayout(param_vulkan->device, &layoutInfo, nullptr, &descriptor_layout);
  if(result != VK_SUCCESS){
    throw std::runtime_error("failed to create descriptor set layout!");
  }

  //---------------------------
}
void VK_descriptor::create_descriptor_pool(){
  vector<VkDescriptorPoolSize> vec_pool_size;
  //---------------------------

  //UBO
  VkDescriptorPoolSize pool_ubo{};
  pool_ubo.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
  pool_ubo.descriptorCount = static_cast<uint32_t>(param_vulkan->max_frame);
  vec_pool_size.push_back(pool_ubo);

  //Sampler
  VkDescriptorPoolSize pool_sampler{};
  pool_sampler.type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
  pool_sampler.descriptorCount = static_cast<uint32_t>(param_vulkan->max_frame);
  vec_pool_size.push_back(pool_sampler);

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
void VK_descriptor::create_descriptor_set(){
  VK_texture* vk_texture = engineManager->get_vk_texture();
  VK_uniform* vk_uniform = engineManager->get_vk_uniform();
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
  VkResult result = vkAllocateDescriptorSets(param_vulkan->device, &allocInfo, descriptor_set.data());
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

    /*
    //Texture to GPU
    descriptor_write[1].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    descriptor_write[1].dstSet = descriptor_set[i];
    descriptor_write[1].dstBinding = 1;
    descriptor_write[1].dstArrayElement = 0;
    descriptor_write[1].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    descriptor_write[1].descriptorCount = 1;
    descriptor_write[1].pImageInfo = &texture.imageInfo;
    */

    vkUpdateDescriptorSets(param_vulkan->device, 1, &descriptor_write, 0, nullptr);
  }

  this->fill_vec_frame(descriptor_set);

  //---------------------------
}

//update function
