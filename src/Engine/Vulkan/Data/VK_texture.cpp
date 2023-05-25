#include "VK_texture.h"
#include "VK_buffer.h"

#include "../Engine.h"
#include "../Param_vulkan.h"
#include "../Device/VK_device.h"
#include "../Device/VK_physical_device.h"
#include "../Command/VK_command.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../../../../extern/image/stb_image.h"


//Constructor / Destructor
VK_texture::VK_texture(Engine* engineManager){
  //---------------------------

  this->engineManager = engineManager;
  this->param_vulkan = engineManager->get_param_vulkan();
  this->vk_device = engineManager->get_vk_device();
  this->vk_buffer = engineManager->get_vk_buffer();
  this->vk_physical_device = engineManager->get_vk_physical_device();

  //---------------------------
}
VK_texture::~VK_texture(){}

//Main function
void VK_texture::load_texture(Object* object){
  //---------------------------

  Struct_texture* texture = new Struct_texture();
  texture->path_texture = object->path_text;
  texture->imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;

  this->create_texture_image(texture);
  this->create_texture_image_view(texture);
  this->create_texture_sampler(texture);

  object->list_texture.push_back(texture);

  //---------------------------
}
void VK_texture::cleanup_texture(Object* object){
  //---------------------------

  for(int i=0; i<object->list_texture.size(); i++){
    Struct_texture* texture = *next(object->list_texture.begin(), i);

    vkDestroySampler(param_vulkan->device, texture->textureSampler, nullptr);
    vkDestroyImageView(param_vulkan->device, texture->textureImageView, nullptr);
    vkDestroyImage(param_vulkan->device, texture->textureImage, nullptr);
    vkFreeMemory(param_vulkan->device, texture->textureImageMemory, nullptr);
  }

  //---------------------------
}

//Texture creation
void VK_texture::create_texture_image(Struct_texture* texture){
  //---------------------------

  int texWidth, texHeight, texChannels;
  stbi_uc* pixels = stbi_load(texture->path_texture.c_str(), &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);
  VkDeviceSize imageSize = texWidth * texHeight * 4;
  if(!pixels){
    throw std::runtime_error("failed to load texture image!");
  }

  VkBuffer stagingBuffer;
  VkDeviceMemory stagingBufferMemory;
  vk_buffer->create_gpu_buffer(imageSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, stagingBuffer);
  vk_buffer->bind_buffer_memory(memory_cpu_visible_gpu, stagingBuffer, stagingBufferMemory);

  void* data;
  vkMapMemory(param_vulkan->device, stagingBufferMemory, 0, imageSize, 0, &data);
  memcpy(data, pixels, static_cast<size_t>(imageSize));
  vkUnmapMemory(param_vulkan->device, stagingBufferMemory);

  stbi_image_free(pixels);

  this->create_image(texWidth, texHeight, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT, memory_gpu, texture->textureImage, texture->textureImageMemory);

  vk_buffer->transitionImageLayout(texture->textureImage, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
  this->copy_buffer_to_image(stagingBuffer, texture->textureImage, static_cast<uint32_t>(texWidth), static_cast<uint32_t>(texHeight));
  vk_buffer->transitionImageLayout(texture->textureImage, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);

  vkDestroyBuffer(param_vulkan->device, stagingBuffer, nullptr);
  vkFreeMemory(param_vulkan->device, stagingBufferMemory, nullptr);

  //---------------------------
}
void VK_texture::create_texture_image_view(Struct_texture* texture){
  //---------------------------

  texture->textureImageView = create_image_view(texture->textureImage, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_ASPECT_COLOR_BIT);

  //---------------------------
}
void VK_texture::create_texture_sampler(Struct_texture* texture){
  //---------------------------

  VkPhysicalDeviceProperties properties{};
  vkGetPhysicalDeviceProperties(param_vulkan->physical_device, &properties);

  VkSamplerCreateInfo samplerInfo{};
  samplerInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
  samplerInfo.magFilter = VK_FILTER_LINEAR;
  samplerInfo.minFilter = VK_FILTER_LINEAR;
  samplerInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;
  samplerInfo.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;
  samplerInfo.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT;
  samplerInfo.anisotropyEnable = VK_TRUE;
  samplerInfo.maxAnisotropy = properties.limits.maxSamplerAnisotropy;
  samplerInfo.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
  samplerInfo.unnormalizedCoordinates = VK_FALSE;
  samplerInfo.compareEnable = VK_FALSE;
  samplerInfo.compareOp = VK_COMPARE_OP_ALWAYS;
  samplerInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;

  VkResult result = vkCreateSampler(param_vulkan->device, &samplerInfo, nullptr, &texture->textureSampler);
  if(result != VK_SUCCESS){
    throw std::runtime_error("failed to create texture sampler!");
  }

  //---------------------------
}

//Generic image creation
VkImageView VK_texture::create_image_view(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags){
  //---------------------------

  VkImageViewCreateInfo viewInfo{};
  viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
  viewInfo.image = image;
  viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
  viewInfo.format = format;
  viewInfo.subresourceRange.aspectMask = aspectFlags;
  viewInfo.subresourceRange.baseMipLevel = 0;
  viewInfo.subresourceRange.levelCount = 1;
  viewInfo.subresourceRange.baseArrayLayer = 0;
  viewInfo.subresourceRange.layerCount = 1;

  VkImageView imageView;
  VkResult result = vkCreateImageView(param_vulkan->device, &viewInfo, nullptr, &imageView);
  if(result != VK_SUCCESS){
    throw std::runtime_error("failed to create texture image view!");
  }

  //---------------------------
  return imageView;
}
void VK_texture::create_image(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory){
  //---------------------------

  VkImageCreateInfo imageInfo{};
  imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
  imageInfo.imageType = VK_IMAGE_TYPE_2D;
  imageInfo.extent.width = width;
  imageInfo.extent.height = height;
  imageInfo.extent.depth = 1;
  imageInfo.mipLevels = 1;
  imageInfo.arrayLayers = 1;
  imageInfo.format = format;
  imageInfo.tiling = tiling;
  imageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
  imageInfo.usage = usage;
  imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
  imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

  VkResult result = vkCreateImage(param_vulkan->device, &imageInfo, nullptr, &image);
  if(result != VK_SUCCESS){
    throw std::runtime_error("failed to create image!");
  }

  VkMemoryRequirements memRequirements;
  vkGetImageMemoryRequirements(param_vulkan->device, image, &memRequirements);

  VkMemoryAllocateInfo allocInfo{};
  allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
  allocInfo.allocationSize = memRequirements.size;
  allocInfo.memoryTypeIndex = vk_buffer->findMemoryType(memRequirements.memoryTypeBits, properties);

  result = vkAllocateMemory(param_vulkan->device, &allocInfo, nullptr, &imageMemory);
  if(result != VK_SUCCESS){
    throw std::runtime_error("failed to allocate image memory!");
  }

  vkBindImageMemory(param_vulkan->device, image, imageMemory, 0);

  //---------------------------
}
void VK_texture::copy_buffer_to_image(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height){
  VK_command* vk_command = engineManager->get_vk_command();
  //---------------------------

  VkCommandBuffer command_buffer = vk_command->command_buffer_begin();

  VkBufferImageCopy region{};
  region.bufferOffset = 0;
  region.bufferRowLength = 0;
  region.bufferImageHeight = 0;

  region.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
  region.imageSubresource.mipLevel = 0;
  region.imageSubresource.baseArrayLayer = 0;
  region.imageSubresource.layerCount = 1;

  region.imageOffset = {0, 0, 0};
  region.imageExtent = {
    width,
    height,
    1
  };

  vkCmdCopyBufferToImage(command_buffer, buffer, image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &region);

  vk_command->command_buffer_end(command_buffer);

  //---------------------------
}
