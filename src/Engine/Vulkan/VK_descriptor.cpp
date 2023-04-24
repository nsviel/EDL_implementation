#include "VK_descriptor.h"
#include "VK_device.h"
#include "VK_uniform.h"
#include "Engine_vulkan.h"


//Constructor / Destructor
VK_descriptor::VK_descriptor(Engine_vulkan* engine_vulkan){
  //---------------------------

  this->engine_vulkan = engine_vulkan;
  this->vk_device = engine_vulkan->get_vk_device();

  //---------------------------
}
VK_descriptor::~VK_descriptor(){}

//Main function
void VK_descriptor::create_descriptorSet_layout(){
  VkDevice device = vk_device->get_device();
  //---------------------------

  VkDescriptorSetLayoutBinding uboLayoutBinding{};
  uboLayoutBinding.binding = 0;
  uboLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
  uboLayoutBinding.descriptorCount = 1;
  uboLayoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
  uboLayoutBinding.pImmutableSamplers = nullptr; // Optional

  VkDescriptorSetLayoutCreateInfo layoutInfo{};
  layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
  layoutInfo.bindingCount = 1;
  layoutInfo.pBindings = &uboLayoutBinding;

  VkResult result = vkCreateDescriptorSetLayout(device, &layoutInfo, nullptr, &descriptorSetLayout);
  if(result != VK_SUCCESS){
    throw std::runtime_error("failed to create descriptor set layout!");
  }

  //---------------------------
}
void VK_descriptor::create_descriptor_pool() {
  VkDevice device = vk_device->get_device();
  //---------------------------

  VkDescriptorPoolSize poolSize{};
  poolSize.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
  poolSize.descriptorCount = static_cast<uint32_t>(MAX_FRAMES_IN_FLIGHT);

  VkDescriptorPoolCreateInfo poolInfo{};
  poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
  poolInfo.poolSizeCount = 1;
  poolInfo.pPoolSizes = &poolSize;
  poolInfo.maxSets = static_cast<uint32_t>(MAX_FRAMES_IN_FLIGHT);

  VkResult result = vkCreateDescriptorPool(device, &poolInfo, nullptr, &descriptorPool);
  if(result != VK_SUCCESS){
    throw std::runtime_error("failed to create descriptor pool!");
  }

  //---------------------------
}
void VK_descriptor::create_descriptor_sets() {
  VK_uniform* vk_uniform = engine_vulkan->get_vk_uniform();
  VkDevice device = vk_device->get_device();
  std::vector<VkBuffer> uniformBuffers = vk_uniform->get_uniformBuffers();
  //---------------------------

  std::vector<VkDescriptorSetLayout> layouts(MAX_FRAMES_IN_FLIGHT, descriptorSetLayout);
  VkDescriptorSetAllocateInfo allocInfo{};
  allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
  allocInfo.descriptorPool = descriptorPool;
  allocInfo.descriptorSetCount = static_cast<uint32_t>(MAX_FRAMES_IN_FLIGHT);
  allocInfo.pSetLayouts = layouts.data();

  descriptorSets.resize(MAX_FRAMES_IN_FLIGHT);
  VkResult result = vkAllocateDescriptorSets(device, &allocInfo, descriptorSets.data());
  if(result != VK_SUCCESS){
    throw std::runtime_error("failed to allocate descriptor sets!");
  }

  for(size_t i=0; i<MAX_FRAMES_IN_FLIGHT; i++){
    VkDescriptorBufferInfo bufferInfo{};
    bufferInfo.buffer = uniformBuffers[i];
    bufferInfo.offset = 0;
    bufferInfo.range = sizeof(UniformBufferObject);

    VkWriteDescriptorSet descriptorWrite{};
    descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    descriptorWrite.dstSet = descriptorSets[i];
    descriptorWrite.dstBinding = 0;
    descriptorWrite.dstArrayElement = 0;
    descriptorWrite.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    descriptorWrite.descriptorCount = 1;
    descriptorWrite.pBufferInfo = &bufferInfo;
    descriptorWrite.pImageInfo = nullptr; // Optional
    descriptorWrite.pTexelBufferView = nullptr; // Optional

    vkUpdateDescriptorSets(device, 1, &descriptorWrite, 0, nullptr);
  }

  //---------------------------
}
void VK_descriptor::cleanup(){
  VkDevice device = vk_device->get_device();
  //---------------------------

  vkDestroyDescriptorPool(device, descriptorPool, nullptr);
  vkDestroyDescriptorSetLayout(device, descriptorSetLayout, nullptr);

  //---------------------------
}

//Subfunctions
