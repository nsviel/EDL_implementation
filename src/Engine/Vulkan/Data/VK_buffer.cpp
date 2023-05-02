#include "VK_buffer.h"
#include "VK_texture.h"
#include "VK_descriptor.h"

#include "../Command/VK_command.h"
#include "../Engine_vulkan.h"
#include "../Device/VK_device.h"

#include "../../Node_engine.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "../../../../extern/tiny_obj_loader.h"



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
void VK_buffer::load_model(){
  //---------------------------
  const std::string MODEL_PATH = "../src/Engine/Texture/viking_room.obj";
  const std::string TEXTURE_PATH = "../src/Engine/Texture/viking_room.png";

  Cloud* cloud = new Cloud();

  tinyobj::attrib_t attrib;
  std::vector<tinyobj::shape_t> shapes;
  std::vector<tinyobj::material_t> materials;
  std::string warn, err;

  bool load_ok = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, MODEL_PATH.c_str());
  if(!load_ok){
    throw std::runtime_error(warn + err);
  }

  std::vector<Vertex> vertices;
  for(const auto& shape : shapes){
    for(const auto& index : shape.mesh.indices){
      Vertex vertex;
      vertex.pos = {
        attrib.vertices[3 * index.vertex_index + 0],
        attrib.vertices[3 * index.vertex_index + 1],
        attrib.vertices[3 * index.vertex_index + 2]
      };
      vertex.texCoord = {
        attrib.texcoords[2 * index.texcoord_index + 0],
        1.0f - attrib.texcoords[2 * index.texcoord_index + 1]
      };
      vertex.color = {1.0f, 1.0f, 1.0f};
      vertices.push_back(vertex);

      cloud->xyz.push_back(vertex.pos);
      cloud->rgb.push_back(vec4(1, 1, 1, 1));
      cloud->uv.push_back(vertex.texCoord);
    }
  }

  cloud->path_file = MODEL_PATH;
  cloud->path_texture = TEXTURE_PATH;


  this->insert_model_in_engine(vertices, cloud->path_texture);

  //---------------------------
}
void VK_buffer::insert_model_in_engine(std::vector<Vertex> vertices, std::string tex_path){
  VK_texture* vk_texture = engine_vulkan->get_vk_texture();
  //---------------------------

  vk_texture->load_texture(tex_path);
  this->create_vertex_buffer(vertices);
  vk_descriptor->create_descriptor_set();

  //---------------------------
}
void VK_buffer::cleanup(){
  VkDevice device = vk_device->get_device();
  //---------------------------

  vkDestroyBuffer(device, buffer_vertex, nullptr);
  vkFreeMemory(device, buffer_vertex_memory, nullptr);

  //---------------------------
}

//Buffer functions
void VK_buffer::create_vertex_buffer(std::vector<Vertex> vertices){
  VkDevice device = vk_device->get_device();
  //---------------------------

  VkDeviceSize size = sizeof(vertices[0]) * vertices.size();
  VkBuffer stagingBuffer;
  VkDeviceMemory stagingBufferMemory;

  VkBufferUsageFlags usage = VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
  VkMemoryPropertyFlags properties = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;
  this->create_buffer(size, usage, properties, stagingBuffer, stagingBufferMemory);

  //Filling the vertex buffer
  void* data;
  vkMapMemory(device, stagingBufferMemory, 0, size, 0, &data);
  memcpy(data, vertices.data(), (size_t)size);
  vkUnmapMemory(device, stagingBufferMemory);

  usage = VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
  properties = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
  this->create_buffer(size, usage, properties, buffer_vertex, buffer_vertex_memory);
  this->copy_buffer(stagingBuffer, buffer_vertex, size);

  vkDestroyBuffer(device, stagingBuffer, nullptr);
  vkFreeMemory(device, stagingBufferMemory, nullptr);

  //---------------------------
}
void VK_buffer::create_buffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory){
  VkDevice device = vk_device->get_device();
  //---------------------------

  VkBufferCreateInfo bufferInfo{};
  bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
  bufferInfo.size = size;
  bufferInfo.usage = usage;
  bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

  VkResult result = vkCreateBuffer(device, &bufferInfo, nullptr, &buffer);
  if(result != VK_SUCCESS){
    throw std::runtime_error("failed to create buffer!");
  }

  VkMemoryRequirements memRequirements;
  vkGetBufferMemoryRequirements(device, buffer, &memRequirements);

  VkMemoryAllocateInfo allocInfo{};
  allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
  allocInfo.allocationSize = memRequirements.size;
  allocInfo.memoryTypeIndex = findMemoryType(memRequirements.memoryTypeBits, properties);

  result = vkAllocateMemory(device, &allocInfo, nullptr, &bufferMemory);
  if(result != VK_SUCCESS){
    throw std::runtime_error("failed to allocate buffer memory!");
  }

  vkBindBufferMemory(device, buffer, bufferMemory, 0);

  //---------------------------
}
void VK_buffer::copy_buffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size){
  //---------------------------

  VkCommandBuffer commandBuffer = beginSingleTimeCommands();

  VkBufferCopy copyRegion{};
  copyRegion.size = size;
  vkCmdCopyBuffer(commandBuffer, srcBuffer, dstBuffer, 1, &copyRegion);

  this->endSingleTimeCommands(commandBuffer);

  //---------------------------
}

//Specific function
VkCommandBuffer VK_buffer::beginSingleTimeCommands(){
  VK_command* vk_command = engine_vulkan->get_vk_command();
  VkCommandPool commandPool = vk_command->get_command_pool();
  VkDevice device = vk_device->get_device();
  //---------------------------

  VkCommandBufferAllocateInfo allocInfo{};
  allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
  allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
  allocInfo.commandPool = commandPool;
  allocInfo.commandBufferCount = 1;

  VkCommandBuffer commandBuffer;
  vkAllocateCommandBuffers(device, &allocInfo, &commandBuffer);

  VkCommandBufferBeginInfo beginInfo{};
  beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
  beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

  vkBeginCommandBuffer(commandBuffer, &beginInfo);

  //---------------------------
  return commandBuffer;
}
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
void VK_buffer::endSingleTimeCommands(VkCommandBuffer commandBuffer){
  VK_command* vk_command = engine_vulkan->get_vk_command();
  VkCommandPool commandPool = vk_command->get_command_pool();
  VkDevice device = vk_device->get_device();
  VkQueue queue_graphics = vk_device->get_queue_graphics();
  //---------------------------

  vkEndCommandBuffer(commandBuffer);

  VkSubmitInfo submitInfo{};
  submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
  submitInfo.commandBufferCount = 1;
  submitInfo.pCommandBuffers = &commandBuffer;

  vkQueueSubmit(queue_graphics, 1, &submitInfo, VK_NULL_HANDLE);
  vkQueueWaitIdle(queue_graphics);

  vkFreeCommandBuffers(device, commandPool, 1, &commandBuffer);

  //---------------------------
}
void VK_buffer::transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout){
  //---------------------------

  VkCommandBuffer commandBuffer = beginSingleTimeCommands();

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

  this->endSingleTimeCommands(commandBuffer);

  //---------------------------
}
