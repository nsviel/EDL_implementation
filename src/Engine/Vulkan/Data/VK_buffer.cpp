#include "VK_buffer.h"
#include "VK_texture.h"
#include "VK_descriptor.h"

#include "../Engine.h"
#include "../Param_vulkan.h"
#include "../Command/VK_command.h"
#include "../Device/VK_device.h"
#include "../Device/VK_physical_device.h"


//Constructor / Destructor
VK_buffer::VK_buffer(Engine* engineManager){
  //---------------------------

  this->engineManager = engineManager;
  this->param_vulkan = engineManager->get_param_vulkan();
  this->vk_device = engineManager->get_vk_device();
  this->vk_physical_device = engineManager->get_vk_physical_device();

  //---------------------------
}
VK_buffer::~VK_buffer(){}

//Main function
void VK_buffer::cleanup_object(Object* object){
  //---------------------------

  //Location buffer
  vkDestroyBuffer(param_vulkan->device, object->vbo_xyz, nullptr);
  vkFreeMemory(param_vulkan->device, object->mem_xyz, nullptr);

  //Location buffer
  if(object->rgb.size() != 0){
    vkDestroyBuffer(param_vulkan->device, object->vbo_rgb, nullptr);
    vkFreeMemory(param_vulkan->device, object->mem_rgb, nullptr);
  }

  //Location buffer
  if(object->uv.size() != 0){
    vkDestroyBuffer(param_vulkan->device, object->vbo_uv, nullptr);
    vkFreeMemory(param_vulkan->device, object->mem_uv, nullptr);
  }

  //---------------------------
}

//Data buffer functions
void VK_buffer::create_buffer_xyz(Object* object, std::vector<vec3> vertices){
  //---------------------------
sayHello();
  VkDeviceSize size = sizeof(vertices[0]) * vertices.size();

  VkBuffer staging_buffer;
  VkDeviceMemory staging_buffer_memory;
  VkBufferUsageFlags usage = VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
  VkMemoryPropertyFlags properties = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;
  this->create_buffer(size, usage, staging_buffer);
  this->bind_buffer_memory(properties, staging_buffer, staging_buffer_memory);

  //Copy the vertex data from the CPU to the GPU
  void* data;
  vkMapMemory(param_vulkan->device, staging_buffer_memory, 0, size, 0, &data);
  memcpy(data, vertices.data(), (size_t)size);
  vkUnmapMemory(param_vulkan->device, staging_buffer_memory);

  usage = VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
  properties = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
  this->create_buffer(size, usage, object->vbo_xyz);
  this->bind_buffer_memory(properties, object->vbo_xyz, object->mem_xyz);
  this->copy_buffer_to_gpu(staging_buffer, object->vbo_xyz, size);

  vkDestroyBuffer(param_vulkan->device, staging_buffer, nullptr);
  vkFreeMemory(param_vulkan->device, staging_buffer_memory, nullptr);

  //---------------------------
}
void VK_buffer::create_buffer_rgb(Object* object, std::vector<vec4> vertices){
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
  vkMapMemory(param_vulkan->device, staging_buffer_memory, 0, size, 0, &data);
  memcpy(data, vertices.data(), (size_t)size);
  vkUnmapMemory(param_vulkan->device, staging_buffer_memory);

  usage = VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
  properties = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
  this->create_buffer(size, usage, object->vbo_rgb);
  this->bind_buffer_memory(properties, object->vbo_rgb, object->mem_rgb);
  this->copy_buffer_to_gpu(staging_buffer, object->vbo_rgb, size);

  vkDestroyBuffer(param_vulkan->device, staging_buffer, nullptr);
  vkFreeMemory(param_vulkan->device, staging_buffer_memory, nullptr);

  //---------------------------
}
void VK_buffer::create_buffer_uv(Object* object, std::vector<vec2> vertices){
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
  vkMapMemory(param_vulkan->device, staging_buffer_memory, 0, size, 0, &data);
  memcpy(data, vertices.data(), (size_t)size);
  vkUnmapMemory(param_vulkan->device, staging_buffer_memory);

  usage = VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
  properties = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
  this->create_buffer(size, usage, object->vbo_uv);
  this->bind_buffer_memory(properties, object->vbo_uv, object->mem_uv);
  this->copy_buffer_to_gpu(staging_buffer, object->vbo_uv, size);

  vkDestroyBuffer(param_vulkan->device, staging_buffer, nullptr);
  vkFreeMemory(param_vulkan->device, staging_buffer_memory, nullptr);

  //---------------------------
}

//Buffer functions
void VK_buffer::create_buffer(VkDeviceSize size, VkBufferUsageFlags usage, VkBuffer& buffer){
  //---------------------------

  //Buffer creation
  VkBufferCreateInfo bufferInfo{};
  bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
  bufferInfo.size = size;
  bufferInfo.usage = usage;
  bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

  VkResult result = vkCreateBuffer(param_vulkan->device, &bufferInfo, nullptr, &buffer);
  if(result != VK_SUCCESS){
    throw std::runtime_error("failed to create buffer!");
  }

  //---------------------------
}
void VK_buffer::bind_buffer_memory(VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory){
  //---------------------------

  //Buffer memory attribution
  VkMemoryRequirements memRequirements;
  vkGetBufferMemoryRequirements(param_vulkan->device, buffer, &memRequirements);

  VkMemoryAllocateInfo allocInfo{};
  allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
  allocInfo.allocationSize = memRequirements.size;
  allocInfo.memoryTypeIndex = findMemoryType(memRequirements.memoryTypeBits, properties);

  //1llocate memory on the GPU
  VkResult result = vkAllocateMemory(param_vulkan->device, &allocInfo, nullptr, &bufferMemory);
  if(result != VK_SUCCESS){
    throw std::runtime_error("failed to allocate buffer memory!");
  }

  vkBindBufferMemory(param_vulkan->device, buffer, bufferMemory, 0);

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
  //---------------------------

  VkPhysicalDeviceMemoryProperties memProperties;
  vkGetPhysicalDeviceMemoryProperties(param_vulkan->physical_device, &memProperties);

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
