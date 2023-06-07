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

  Struct_image* texture = new Struct_image();
  texture->path = path;
  texture->format = VK_FORMAT_R8G8B8A8_SRGB;
  texture->aspect = VK_IMAGE_ASPECT_COLOR_BIT;
  this->create_texture(texture);
  data->binding.list_texture.push_back(texture);

  //---------------------------
}
void VK_texture::clean_texture(Struct_data* data){
  //---------------------------

  for(int i=0; i<data->binding.list_texture.size(); i++){
    Struct_image* texture = *next(data->binding.list_texture.begin(), i);
    vk_image->clean_image(texture);
  }

  //---------------------------
}

//Texture creation
void VK_texture::create_texture(Struct_image* texture){
  //---------------------------

  this->create_texture_from_file(texture);
  vk_image->create_image_view(texture);
  vk_image->create_image_sampler(texture);

  //---------------------------
}
void VK_texture::create_texture_from_file(Struct_image* texture){
  VK_command* vk_command = vk_engine->get_vk_command();
  //---------------------------

  //Load image
  int tex_width, tex_height, tex_channel;
  stbi_uc* tex_data = stbi_load(texture->path.c_str(), &tex_width, &tex_height, &tex_channel, STBI_rgb_alpha);
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
  texture->width = tex_width;
  texture->height = tex_height;
  texture->format = VK_FORMAT_R8G8B8A8_SRGB;
  texture->tiling = VK_IMAGE_TILING_OPTIMAL;
  texture->usage = IMAGE_USAGE_TRANSFERT | IMAGE_USAGE_SAMPLER;
  texture->properties = MEMORY_GPU;
  vk_image->create_image(texture);

  //Image transition from undefined layout to read only layout
  vk_command->image_layout_transition_single(texture, IMAGE_LAYOUT_EMPTY, IMAGE_LAYOUT_TRANSFER);
  this->copy_buffer_to_image(texture, staging_buffer);
  vk_command->image_layout_transition_single(texture, IMAGE_LAYOUT_TRANSFER, IMAGE_LAYOUT_SHADER);

  //Free memory
  stbi_image_free(tex_data);
  vkDestroyBuffer(vk_param->device.device, staging_buffer, nullptr);
  vkFreeMemory(vk_param->device.device, staging_mem, nullptr);

  //---------------------------
}
void VK_texture::copy_buffer_to_image(Struct_image* image, VkBuffer buffer){
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
    image->width,
    image->height,
    1
  };

  vkCmdCopyBufferToImage(command_buffer, buffer, image->image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &region);

  vk_command->singletime_command_buffer_end(command_buffer);

  //---------------------------
}
