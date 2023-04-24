#include "VK_buffer.h"
#include "VK_device.h"
#include "VK_struct.h"
#include "Engine_vulkan.h"

#include "../Node_engine.h"


//Constructor / Destructor
VK_buffer::VK_buffer(Engine_vulkan* engine_vulkan){
  //---------------------------

  this->engine_vulkan = engine_vulkan;
  this->vk_device = engine_vulkan->get_vk_device();

  //---------------------------
}
VK_buffer::~VK_buffer(){}

//Main function
void VK_buffer::create_vertex_buffer() {
  VkDevice device = vk_device->get_device();
  //---------------------------

  VkBufferCreateInfo bufferInfo{};
  bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
  bufferInfo.size = sizeof(vertices[0]) * vertices.size();
  bufferInfo.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
  bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

  VkResult result = vkCreateBuffer(device, &bufferInfo, nullptr, &vertexBuffer);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to create vertex buffer!");
  }

  //Memory requirements
  VkMemoryRequirements memRequirements;
  vkGetBufferMemoryRequirements(device, vertexBuffer, &memRequirements);

  //Memory allocation
  VkMemoryAllocateInfo allocInfo{};
  allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
  allocInfo.allocationSize = memRequirements.size;
  allocInfo.memoryTypeIndex = findMemoryType(memRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

  result = vkAllocateMemory(device, &allocInfo, nullptr, &vertexBufferMemory);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to allocate vertex buffer memory!");
  }

  vkBindBufferMemory(device, vertexBuffer, vertexBufferMemory, 0);

  //Filling the vertex buffer
  void* data;
  vkMapMemory(device, vertexBufferMemory, 0, bufferInfo.size, 0, &data);
  memcpy(data, vertices.data(), (size_t) bufferInfo.size);
  vkUnmapMemory(device, vertexBufferMemory);

  //---------------------------
}
void VK_buffer::cleanup(){
  VkDevice device = vk_device->get_device();
  //---------------------------

  vkDestroyBuffer(device, vertexBuffer, nullptr);
  vkFreeMemory(device, vertexBufferMemory, nullptr);

  //---------------------------
}

//Subfunctions
uint32_t VK_buffer::findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties){
  VkPhysicalDevice physical_device = vk_device->get_physical_device();
  //---------------------------

  VkPhysicalDeviceMemoryProperties memProperties;
  vkGetPhysicalDeviceMemoryProperties(physical_device, &memProperties);

  for(uint32_t i=0; i<memProperties.memoryTypeCount; i++){
    if(typeFilter & (1 << i)){
      return i;
    }
  }

  throw std::runtime_error("failed to find suitable memory type!");

  for(uint32_t i=0; i<memProperties.memoryTypeCount; i++){
    if((typeFilter &(1<<i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties){
      return i;
    }
  }

  //---------------------------
}
