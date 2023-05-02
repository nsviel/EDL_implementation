#include "VK_buffer.h"
#include "VK_texture.h"
#include "VK_descriptor.h"

#include "../Command/VK_command.h"
#include "../Engine_vulkan.h"
#include "../Device/VK_device.h"

#include "../../Node_engine.h"


//Constructor / Destructor
VK_buffer::VK_buffer(Engine_vulkan* engine_vulkan){
  //---------------------------

  this->engine_vulkan = engine_vulkan;
  this->vk_device = engine_vulkan->get_vk_device();
  this->vk_descriptor = engine_vulkan->get_vk_descriptor();

  //---------------------------
}
VK_buffer::~VK_buffer(){}

//Main function
void VK_buffer::insert_model_in_engine(std::vector<Vertex> vertices, std::string tex_path){
  VK_texture* vk_texture = engine_vulkan->get_vk_texture();
  //---------------------------

  vk_texture->load_texture(tex_path);
  this->create_buffer_data(vertices);
  vk_descriptor->create_descriptor_set();

  //---------------------------
}
void VK_buffer::insert_cloud_in_engine(Cloud* cloud){
  VK_texture* vk_texture = engine_vulkan->get_vk_texture();
  //---------------------------

  vk_texture->load_texture(cloud->path_texture);
  this->create_buffer_xyz(cloud, cloud->xyz);
  this->create_buffer_rgb(cloud, cloud->rgb);
  this->create_buffer_uv(cloud, cloud->uv);
  vk_descriptor->create_descriptor_set();

  //---------------------------
}
void VK_buffer::cleanup(Cloud* cloud){
  VkDevice device = vk_device->get_device();
  //---------------------------

  vkDestroyBuffer(device, cloud->vbo_xyz, nullptr);
  vkDestroyBuffer(device, cloud->vbo_rgb, nullptr);
  vkDestroyBuffer(device, cloud->vbo_uv, nullptr);
  vkFreeMemory(device, dev_memory, nullptr);

  //---------------------------
}

//Buffer functions
void VK_buffer::create_buffer_data(std::vector<Vertex> vertices){
  VkDevice device = vk_device->get_device();
  //---------------------------
/*
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
  this->create_buffer(size, usage, buffer_vertex);
  this->bind_buffer_memory(properties, buffer_vertex, dev_memory);
  this->copy_buffer_to_gpu(staging_buffer, buffer_vertex, size);

  vkDestroyBuffer(device, staging_buffer, nullptr);
  vkFreeMemory(device, staging_buffer_memory, nullptr);*/

  //---------------------------
}
void VK_buffer::create_buffer_uv(Cloud* cloud, std::vector<vec2> vertices){
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
  this->create_buffer(size, usage, cloud->vbo_uv);
  this->bind_buffer_memory(properties, cloud->vbo_uv, dev_memory);
  this->copy_buffer_to_gpu(staging_buffer, cloud->vbo_uv, size);

  vkDestroyBuffer(device, staging_buffer, nullptr);
  vkFreeMemory(device, staging_buffer_memory, nullptr);

  //---------------------------
}
void VK_buffer::create_buffer_xyz(Cloud* cloud, std::vector<vec3> vertices){
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
  this->create_buffer(size, usage, cloud->vbo_xyz);
  this->bind_buffer_memory(properties, cloud->vbo_xyz, dev_memory);
  this->copy_buffer_to_gpu(staging_buffer, cloud->vbo_xyz, size);

  vkDestroyBuffer(device, staging_buffer, nullptr);
  vkFreeMemory(device, staging_buffer_memory, nullptr);

  //---------------------------
}
void VK_buffer::create_buffer_rgb(Cloud* cloud, std::vector<vec4> vertices){
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
  this->create_buffer(size, usage, cloud->vbo_rgb);
  this->bind_buffer_memory(properties, cloud->vbo_rgb, dev_memory);
  this->copy_buffer_to_gpu(staging_buffer, cloud->vbo_rgb, size);

  vkDestroyBuffer(device, staging_buffer, nullptr);
  vkFreeMemory(device, staging_buffer_memory, nullptr);

  //---------------------------
}

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
  VK_command* vk_command = engine_vulkan->get_vk_command();
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
  VK_command* vk_command = engine_vulkan->get_vk_command();
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
