#ifndef VK_TEXTURE_H
#define VK_TEXTURE_H

#include "../../Struct/struct_texture.h"
#include "../../Struct/struct_data.h"
#include "../../Struct/struct_attachment.h"
#include "../../Struct/typedef.h"
#include "../../../../common.h"

class VK_engine;
class VK_param;
class VK_buffer;
class VK_image;


class VK_texture
{
public:
  //Constructor / Destructor
  VK_texture(VK_engine* vk_engine);
  ~VK_texture();

public:
  //Main functions
  void load_texture(Struct_data* object, string path);
  void clean_texture(Struct_data* object);

  //Texture creation
  void create_texture_image(Struct_texture* texture);
  void create_texture_view(Struct_texture* texture);
  void create_texture_sampler(Struct_texture* texture);

  //Generic image creation
  void create_image_view(Struct_image* image);
  void create_image(Struct_image* image);
  void copy_buffer_to_image(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);

private:
  VK_engine* vk_engine;
  VK_param* vk_param;
  VK_buffer* vk_buffer;
  VK_image* vk_image;
};

#endif
