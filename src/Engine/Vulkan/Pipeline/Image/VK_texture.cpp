#include "VK_texture.h"
#include "VK_image.h"

#include "../../VK_engine.h"
#include "../../VK_param.h"
#include "../../Data/VK_buffer.h"
#include "../../Instance/Device/VK_device.h"
#include "../../Instance/Device/VK_physical_device.h"
#include "../../Pipeline/Command/VK_command.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../../../../../extern/image/stb_image.h"


//Constructor / Destructor
VK_texture::VK_texture(VK_engine* vk_engine){
  //---------------------------

  this->vk_engine = vk_engine;
  this->vk_param = vk_engine->get_vk_param();
  this->vk_buffer = vk_engine->get_vk_buffer();
  this->vk_image = vk_engine->get_vk_image();

  //---------------------------
}
VK_texture::~VK_texture(){}

//Main function
void VK_texture::load_texture(Struct_data* data, string path){
  //---------------------------

  Struct_texture* texture = new Struct_texture();
  texture->path_texture = path;
  texture->image_info.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;

  this->create_texture_image(texture);
  this->create_texture_view(texture);
  this->create_texture_sampler(texture);

  data->binding.list_texture.push_back(texture);

  //---------------------------
}
void VK_texture::clean_texture(Struct_data* data){
  //---------------------------

  for(int i=0; i<data->binding.list_texture.size(); i++){
    Struct_texture* texture = *next(data->binding.list_texture.begin(), i);

    vkDestroySampler(vk_param->device.device, texture->sampler, nullptr);
    vkDestroyImageView(vk_param->device.device, texture->view, nullptr);
    vkDestroyImage(vk_param->device.device, texture->image, nullptr);
    vkFreeMemory(vk_param->device.device, texture->mem, nullptr);
  }

  //---------------------------
}

//Texture creation
void VK_texture::create_texture_image(Struct_texture* texture){
  //---------------------------

  //Load image
  int tex_width, tex_height, tex_channel;
  stbi_uc* tex_data = stbi_load(texture->path_texture.c_str(), &tex_width, &tex_height, &tex_channel, STBI_rgb_alpha);
  VkDeviceSize tex_size = tex_width * tex_height * 4;
  if(!tex_data){
    throw std::runtime_error("failed to load texture image!");
  }

  //Create stagging buffer
  VkBuffer staging_buffer;
  VkDeviceMemory staging_mem;
  vk_buffer->create_gpu_buffer(tex_size, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, staging_buffer);
  vk_buffer->bind_buffer_memory(MEMORY_SHARED_CPU_GPU, staging_buffer, staging_mem);

  //Copy data to stagging buffer
  void* data;
  vkMapMemory(vk_param->device.device, staging_mem, 0, tex_size, 0, &data);
  memcpy(data, tex_data, static_cast<size_t>(tex_size));
  vkUnmapMemory(vk_param->device.device, staging_mem);

  //Create image
  Struct_image* image = new Struct_image();
  image->width = tex_width;
  image->height = tex_height;
  image->format = VK_FORMAT_R8G8B8A8_SRGB;
  image->tiling = VK_IMAGE_TILING_OPTIMAL;
  image->usage = IMAGE_USAGE_TRANSFERT;
  image->properties = MEMORY_GPU;
  image->image = texture->image;
  image->mem = texture->mem;

  this->create_image(image);

  texture->image = image->image;
  texture->mem = image->mem;

  //Image transition from undefined layout to read only layout
  vk_image->transition_layout_image(texture->image, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
  this->copy_buffer_to_image(staging_buffer, texture->image, static_cast<uint32_t>(tex_width), static_cast<uint32_t>(tex_height));
  vk_image->transition_layout_image(texture->image, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);

  //Free memory
  stbi_image_free(tex_data);
  vkDestroyBuffer(vk_param->device.device, staging_buffer, nullptr);
  vkFreeMemory(vk_param->device.device, staging_mem, nullptr);

  //---------------------------
}
void VK_texture::create_texture_view(Struct_texture* texture){
  //---------------------------

  texture->view = create_image_view(texture->image, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_ASPECT_COLOR_BIT);

  //---------------------------
}
void VK_texture::create_texture_sampler(Struct_texture* texture){
  //---------------------------

  VkPhysicalDeviceProperties properties{};
  vkGetPhysicalDeviceProperties(vk_param->device.physical_device, &properties);

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

  VkResult result = vkCreateSampler(vk_param->device.device, &samplerInfo, nullptr, &texture->sampler);
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
  VkResult result = vkCreateImageView(vk_param->device.device, &viewInfo, nullptr, &imageView);
  if(result != VK_SUCCESS){
    throw std::runtime_error("failed to create texture image view!");
  }

  //---------------------------
  return imageView;
}
void VK_texture::create_image(Struct_image* image){
  //---------------------------

  //uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory

  VkImageCreateInfo imageInfo{};
  imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
  imageInfo.imageType = VK_IMAGE_TYPE_2D;
  imageInfo.extent.width = image->width;
  imageInfo.extent.height = image->height;
  imageInfo.extent.depth = 1;
  imageInfo.mipLevels = 1;
  imageInfo.arrayLayers = 1;
  imageInfo.format = image->format;
  imageInfo.tiling = image->tiling;
  imageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
  imageInfo.usage = image->usage;
  imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
  imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

  VkResult result = vkCreateImage(vk_param->device.device, &imageInfo, nullptr, &image->image);
  if(result != VK_SUCCESS){
    throw std::runtime_error("failed to create image!");
  }

  VkMemoryRequirements memRequirements;
  vkGetImageMemoryRequirements(vk_param->device.device, image->image, &memRequirements);

  VkMemoryAllocateInfo allocInfo{};
  allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
  allocInfo.allocationSize = memRequirements.size;
  allocInfo.memoryTypeIndex = vk_buffer->findMemoryType(memRequirements.memoryTypeBits, image->properties);

  result = vkAllocateMemory(vk_param->device.device, &allocInfo, nullptr, &image->mem);
  if(result != VK_SUCCESS){
    throw std::runtime_error("failed to allocate image memory!");
  }

  vkBindImageMemory(vk_param->device.device, image->image, image->mem, 0);

  //---------------------------
}
void VK_texture::copy_buffer_to_image(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height){
  VK_command* vk_command = vk_engine->get_vk_command();
  //---------------------------

  VkCommandBuffer command_buffer = vk_command->singletime_command_buffer_begin();

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

  vk_command->singletime_command_buffer_end(command_buffer);

  //---------------------------
}
