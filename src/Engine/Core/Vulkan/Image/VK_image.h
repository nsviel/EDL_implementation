#ifndef VK_IMAGE_H
#define VK_IMAGE_H

#include "../../../common.h"

class VK_engine;
class VK_param;
class VK_command;
class VK_buffer;
class VK_physical_device;


class VK_image
{
public:
  //Constructor / Destructor
  VK_image(VK_engine* vk_engine);
  ~VK_image();

public:
  void clean_image(Struct_image* image);

  //Generic image creation
  void create_image_view(Struct_image* image);
  void create_image_sampler(Struct_image* texture);
  VkImageView create_image_view(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags);

  //image creation
  void create_image(Struct_image* image);
  void create_image_obj(Struct_image* image);
  void bind_image_to_memory(Struct_image* image);

  //Subfunction
  void compute_mipmap(Struct_image* image);
  void generate_mipmap(Struct_image* image);

private:
  VK_physical_device* vk_physical_device;
  VK_engine* vk_engine;
  VK_param* vk_param;
  VK_command* vk_command;
  VK_buffer* vk_buffer;
};

#endif
