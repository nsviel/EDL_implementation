#include "VK_buffer.h"
#include "VK_texture.h"
#include "VK_descriptor.h"
#include "VK_data.h"

#include "../Command/VK_command.h"
#include "../Engine.h"
#include "../Device/VK_device.h"

#include "../../Node_engine.h"


//Constructor / Destructor
VK_buffer::VK_buffer(Engine* engineManager){
  //---------------------------

  this->engineManager = engineManager;
  this->vk_device = engineManager->get_vk_device();
  this->vk_descriptor = engineManager->get_vk_descriptor();
  this->vk_data = engineManager->get_vk_data();

  //---------------------------
}
VK_buffer::~VK_buffer(){}

//Main function
void VK_buffer::cleanup_object(Object* object){
  VkDevice device = vk_device->get_device();
  //---------------------------

  vkDestroyBuffer(device, object->vbo_xyz, nullptr);
  vkDestroyBuffer(device, object->vbo_rgb, nullptr);
  vkDestroyBuffer(device, object->vbo_uv, nullptr);
  vkFreeMemory(device, object->mem_xyz, nullptr);
  vkFreeMemory(device, object->mem_rgb, nullptr);
  vkFreeMemory(device, object->mem_uv, nullptr);

  //---------------------------
}

//Data buffer functions
void VK_buffer::create_buffer_uv(Object* object, std::vector<vec2> vertices){
  VkDevice device = vk_device->get_device();
  //---------------------------

  VkDeviceSize size = sizeof(vertices[0]) * vertices.size();

  VkBuffer staging_buffer;
  VkDeviceMemory staging_buffer_memory;
  VkBufferUsageFlags usage = VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
  VkMemoryPropertyFlags properties = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;
  this->create_buffer(size, usage, staging_buffer);
  this->bind_buffer_memory(properties, staging_buffer, staging_buffer_memory);

  //Filling the vertex buffer
  void* data;
  vkMapMemory(device, staging_buffer_memory, 0, size, 0, &data);
  memcpy(data, vertices.data(), (size_t)size);
  vkUnmapMemory(device, staging_buffer_memory);

  usage = VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
  properties = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
  this->create_buffer(size, usage, object->vbo_uv);
  this->bind_buffer_memory(properties, object->vbo_uv, object->mem_uv);
  this->copy_buffer_to_gpu(staging_buffer, object->vbo_uv, size);

  vkDestroyBuffer(device, staging_buffer, nullptr);
  vkFreeMemory(device, staging_buffer_memory, nullptr);

  //---------------------------
}
void VK_buffer::create_buffer_xyz(Object* object, std::vector<vec3> vertices){
  VkDevice device = vk_device->get_device();
  //---------------------------

  VkDeviceSize size = sizeof(vertices[0]) * vertices.size();

  VkBuffer staging_buffer;
  VkDeviceMemory staging_buffer_memory;
  VkBufferUsageFlags usage = VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
  VkMemoryPropertyFlags properties = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;
  this->create_buffer(size, usage, staging_buffer);
  this->bind_buffer_memory(properties, staging_buffer, staging_buffer_memory);

  //Copy the vertex data from the CPU to the GPU
  void* data;
  vkMapMemory(device, staging_buffer_memory, 0, size, 0, &data);
  memcpy(data, vertices.data(), (size_t)size);
  vkUnmapMemory(device, staging_buffer_memory);

  usage = VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
  properties = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
  this->create_buffer(size, usage, object->vbo_xyz);
  this->bind_buffer_memory(properties, object->vbo_xyz, object->mem_xyz);
  this->copy_buffer_to_gpu(staging_buffer, object->vbo_xyz, size);

  vkDestroyBuffer(device, staging_buffer, nullptr);
  vkFreeMemory(device, staging_buffer_memory, nullptr);

  //---------------------------
}
void VK_buffer::create_buffer_rgb(Object* object, std::vector<vec4> vertices){
  VkDevice device = vk_device->get_device();
  //---------------------------

  VkDeviceSize size = sizeof(vertices[0]) * vertices.size();

  VkBuffer staging_buffer;
  VkDeviceMemory staging_buffer_memory;
  VkBufferUsageFlags usage = VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
  VkMemoryPropertyFlags properties = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;
  this->create_buffer(size, usage, staging_buffer);
  this->bind_buffer_memory(properties, staging_buffer, staging_buffer_memory);

  //Filling the vertex buffer
  void* data;
  vkMapMemory(device, staging_buffer_memory, 0, size, 0, &data);
  memcpy(data, vertices.data(), (size_t)size);
  vkUnmapMemory(device, staging_buffer_memory);

  usage = VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
  properties = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
  this->create_buffer(size, usage, object->vbo_rgb);
  this->bind_buffer_memory(properties, object->vbo_rgb, object->mem_rgb);
  this->copy_buffer_to_gpu(staging_buffer, object->vbo_rgb, size);

  vkDestroyBuffer(device, staging_buffer, nullptr);
  vkFreeMemory(device, staging_buffer_memory, nullptr);

  //---------------------------
}

//Buffer functions
void VK_buffer::create_buffer(VkDeviceSize size, VkBufferUsageFlags usage, VkBuffer& buffer){
  VkDevice device = vk_device->get_device();
  //---------------------------

  //Buffer creation
  VkBufferCreateInfo bufferInfo{};
  bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
  bufferInfo.size = size;
  bufferInfo.usage = usage;
  bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

  VkResult result = vkCreateBuffer(device, &bufferInfo, nullptr, &buffer);
  if(result != VK_SUCCESS){
    throw std::runtime_error("failed to create buffer!");
  }

  //---------------------------
}
void VK_buffer::bind_buffer_memory(VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory){
  VkDevice device = vk_device->get_device();
  //---------------------------

  //Buffer memory attribution
  VkMemoryRequirements memRequirements;
  vkGetBufferMemoryRequirements(device, buffer, &memRequirements);

  VkMemoryAllocateInfo allocInfo{};
  allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
  allocInfo.allocationSize = memRequirements.size;
  allocInfo.memoryTypeIndex = findMemoryType(memRequirements.memoryTypeBits, properties);

  //1llocate memory on the GPU
  VkResult result = vkAllocateMemory(device, &allocInfo, nullptr, &bufferMemory);
  if(result != VK_SUCCESS){
    throw std::runtime_error("failed to allocate buffer memory!");
  }

  vkBindBufferMemory(device, buffer, bufferMemory, 0);

  //---------------------------
}
void VK_buffer::copy_buffer_to_gpu(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size){
  VK_command* vk_command = engineManager->get_vk_command();
  //---------------------------

  VkCommandBuffer commandBuffer = vk_command->command_buffer_begin();

  VkBufferCopy copyRegion{};
  copyRegion.size = size;
  vkCmdCopyBuffer(commandBuffer, srcBuffer, dstBuffer, 1, &copyRegion);

  vk_command->command_buffer_end(commandBuffer);

  //---------------------------
}

//Specific function
uint32_t VK_buffer::findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties){
  VkPhysicalDevice physical_device = vk_device->get_physical_device();
  //---------------------------

  VkPhysicalDeviceMemoryProperties memProperties;
  vkGetPhysicalDeviceMemoryProperties(physical_device, &memProperties);

  for(uint32_t i=0; i<memProperties.memoryTypeCount; i++){
    if((typeFilter &(1<<i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties){
      return i;
    }
  }

  throw std::runtime_error("failed to find suitable memory type!");

  //---------------------------
}
void VK_buffer::transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout){
  VK_command* vk_command = engineManager->get_vk_command();
  //---------------------------

  VkCommandBuffer commandBuffer = vk_command->command_buffer_begin();

  VkImageMemoryBarrier barrier{};
  barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
  barrier.oldLayout = oldLayout;
  barrier.newLayout = newLayout;
  barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
  barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
  barrier.image = image;
  barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
  barrier.subresourceRange.baseMipLevel = 0;
  barrier.subresourceRange.levelCount = 1;
  barrier.subresourceRange.baseArrayLayer = 0;
  barrier.subresourceRange.layerCount = 1;

  VkPipelineStageFlags sourceStage;
  VkPipelineStageFlags destinationStage;

  if(oldLayout == VK_IMAGE_LAYOUT_UNDEFINED && newLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL){
    barrier.srcAccessMask = 0;
    barrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;

    sourceStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
    destinationStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
  }else if(oldLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL && newLayout == VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL){
    barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
    barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

    sourceStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
    destinationStage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
  }else{
    throw std::invalid_argument("unsupported layout transition!");
  }

  vkCmdPipelineBarrier(
    commandBuffer,
    sourceStage, destinationStage,
    0,
    0, nullptr,
    0, nullptr,
    1, &barrier
  );

  vk_command->command_buffer_end(commandBuffer);

  //---------------------------
}
