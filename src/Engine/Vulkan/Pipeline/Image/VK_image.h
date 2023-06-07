#ifndef VK_IMAGE_H
#define VK_IMAGE_H

#include "../../../../common.h"

class VK_engine;
class VK_param;
class VK_command;
class VK_buffer;


class VK_image
{
public:
  //Constructor / Destructor
  VK_image(VK_engine* vk_engine);
  ~VK_image();

public:
  //Generic image creation
  void create_image(Struct_image* image);
  void create_image_view(Struct_image* image);
  void create_image_sampler(Struct_image* texture);

private:
  VK_engine* vk_engine;
  VK_param* vk_param;
  VK_command* vk_command;
  VK_buffer* vk_buffer;
};

#endif
