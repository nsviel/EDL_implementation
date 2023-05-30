#include "VK_buffer.h"
#include "VK_texture.h"

#include "../Shader/VK_descriptor.h"
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
void VK_buffer::create_buffer(Struct_data* data){
  //---------------------------

  this->create_buffer_xyz(data);

  if(data->has_rgb){
    this->create_buffer_rgb(data);
  }

  if(data->has_uv){
    this->create_buffer_uv(data);
  }

  if(data->object->path_text != ""){
    //vk_texture->load_texture(object);
  }

  //---------------------------
}
void VK_buffer::clean_data(Struct_data* data){
  //---------------------------

  //Location buffer
  vkDestroyBuffer(param_vulkan->device.device, data->xyz.vbo, nullptr);
  vkFreeMemory(param_vulkan->device.device, data->xyz.mem, nullptr);

  //Location buffer
  if(data->has_rgb){
    vkDestroyBuffer(param_vulkan->device.device, data->rgb.vbo, nullptr);
    vkFreeMemory(param_vulkan->device.device, data->rgb.mem, nullptr);
  }

  //Location buffer
  if(data->has_uv){
    vkDestroyBuffer(param_vulkan->device.device, data->uv.vbo, nullptr);
    vkFreeMemory(param_vulkan->device.device, data->uv.mem, nullptr);
  }

  //---------------------------
}

//Data buffer functions
void VK_buffer::create_buffer_xyz(Struct_data* data){
  vector<vec3>& vertices = data->object->xyz;
  VkDeviceSize size = sizeof(vertices[0]) * vertices.size();
  //---------------------------

  VkBuffer staging_buffer;
  VkDeviceMemory staging_buffer_memory;
  this->create_gpu_buffer(size, BUFFER_USAGE_SRC, staging_buffer);
  this->bind_buffer_memory(MEMORY_SHARED_CPU_GPU, staging_buffer, staging_buffer_memory);

  //Copy the vertex data from the CPU to the GPU
  void* data_map;
  vkMapMemory(param_vulkan->device.device, staging_buffer_memory, 0, size, 0, &data_map);
  memcpy(data_map, vertices.data(), (size_t)size);
  vkUnmapMemory(param_vulkan->device.device, staging_buffer_memory);

  this->create_gpu_buffer(size, BUFFER_USAGE_DST_VERTEX, data->xyz.vbo);
  this->bind_buffer_memory(MEMORY_GPU, data->xyz.vbo, data->xyz.mem);
  this->copy_buffer_to_gpu(staging_buffer, data->xyz.vbo, size);

  vkDestroyBuffer(param_vulkan->device.device, staging_buffer, nullptr);
  vkFreeMemory(param_vulkan->device.device, staging_buffer_memory, nullptr);

  //---------------------------
}
void VK_buffer::create_buffer_rgb(Struct_data* data){
  vector<vec4>& vertices = data->object->rgb;
  VkDeviceSize size = sizeof(vertices[0]) * vertices.size();
  //---------------------------

  VkBuffer staging_buffer;
  VkDeviceMemory staging_buffer_memory;
  this->create_gpu_buffer(size, BUFFER_USAGE_SRC, staging_buffer);
  this->bind_buffer_memory(MEMORY_SHARED_CPU_GPU, staging_buffer, staging_buffer_memory);

  //Filling the vertex buffer
  void* data_map;
  vkMapMemory(param_vulkan->device.device, staging_buffer_memory, 0, size, 0, &data_map);
  memcpy(data_map, vertices.data(), (size_t)size);
  vkUnmapMemory(param_vulkan->device.device, staging_buffer_memory);

  this->create_gpu_buffer(size, BUFFER_USAGE_DST_VERTEX, data->rgb.vbo);
  this->bind_buffer_memory(MEMORY_GPU, data->rgb.vbo, data->rgb.mem);
  this->copy_buffer_to_gpu(staging_buffer, data->rgb.vbo, size);

  vkDestroyBuffer(param_vulkan->device.device, staging_buffer, nullptr);
  vkFreeMemory(param_vulkan->device.device, staging_buffer_memory, nullptr);

  //---------------------------
}
void VK_buffer::create_buffer_uv(Struct_data* data){
  vector<vec2>& vertices = data->object->uv;
  VkDeviceSize size = sizeof(vertices[0]) * vertices.size();
  //---------------------------

  //Create empty sized stagging buffer
  VkBuffer staging_buffer;
  VkDeviceMemory staging_buffer_memory;
  this->create_gpu_buffer(size, BUFFER_USAGE_SRC, staging_buffer);
  this->bind_buffer_memory(MEMORY_SHARED_CPU_GPU, staging_buffer, staging_buffer_memory);

  //Fill the created sized stagging buffer
  void* data_map;
  vkMapMemory(param_vulkan->device.device, staging_buffer_memory, 0, size, 0, &data_map);
  memcpy(data_map, vertices.data(), (size_t)size);
  vkUnmapMemory(param_vulkan->device.device, staging_buffer_memory);

  //Copy from stagged buffer to GPU buffer
  this->create_gpu_buffer(size, BUFFER_USAGE_DST_VERTEX, data->uv.vbo);
  this->bind_buffer_memory(MEMORY_GPU, data->uv.vbo, data->uv.mem);
  this->copy_buffer_to_gpu(staging_buffer, data->uv.vbo, size);

  //Destroy created stagging memory
  vkDestroyBuffer(param_vulkan->device.device, staging_buffer, nullptr);
  vkFreeMemory(param_vulkan->device.device, staging_buffer_memory, nullptr);

  //---------------------------
}

//Buffer functions
void VK_buffer::create_gpu_buffer(VkDeviceSize size, VkBufferUsageFlags usage, VkBuffer& buffer){
  //---------------------------

  //Buffer creation
  VkBufferCreateInfo bufferInfo{};
  bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
  bufferInfo.size = size;
  bufferInfo.usage = usage;
  bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

  //Create the GPU buffer
  VkResult result = vkCreateBuffer(param_vulkan->device.device, &bufferInfo, nullptr, &buffer);
  if(result != VK_SUCCESS){
    throw std::runtime_error("failed to create buffer!");
  }

  //---------------------------
}
void VK_buffer::bind_buffer_memory(VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& buffer_memory){
  //---------------------------

  //Get buffer memory requirement
  VkMemoryRequirements buffer_mem_requirement;
  vkGetBufferMemoryRequirements(param_vulkan->device.device, buffer, &buffer_mem_requirement);

  //Buffer allocation info
  VkMemoryAllocateInfo buffer_allocation_info{};
  buffer_allocation_info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
  buffer_allocation_info.allocationSize = buffer_mem_requirement.size;
  buffer_allocation_info.memoryTypeIndex = findMemoryType(buffer_mem_requirement.memoryTypeBits, properties);

  //Allocate buffer memory on the GPU
  VkResult result = vkAllocateMemory(param_vulkan->device.device, &buffer_allocation_info, nullptr, &buffer_memory);
  if(result != VK_SUCCESS){
    throw std::runtime_error("failed to allocate buffer memory!");
  }

  //Bind the buffer with memory on the GPU side
  vkBindBufferMemory(param_vulkan->device.device, buffer, buffer_memory, 0);

  //---------------------------
}
void VK_buffer::copy_buffer_to_gpu(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size){
  VK_command* vk_command = engineManager->get_vk_command();
  //---------------------------

  VkCommandBuffer commandBuffer = vk_command->singletime_command_buffer_begin();

  VkBufferCopy copyRegion{};
  copyRegion.size = size;
  vkCmdCopyBuffer(commandBuffer, srcBuffer, dstBuffer, 1, &copyRegion);

  vk_command->singletime_command_buffer_end(commandBuffer);

  //---------------------------
}

//Specific function
uint32_t VK_buffer::findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties){
  //---------------------------

  VkPhysicalDeviceMemoryProperties memProperties;
  vkGetPhysicalDeviceMemoryProperties(param_vulkan->device.physical_device, &memProperties);

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

  VkCommandBuffer commandBuffer = vk_command->singletime_command_buffer_begin();

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

  vk_command->singletime_command_buffer_end(commandBuffer);

  //---------------------------
}
