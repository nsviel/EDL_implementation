#ifndef VK_IMAGE_H
#define VK_IMAGE_H

#include "../../../../common.h"

class VK_engine;
class VK_param;
class VK_command;


class VK_image
{
public:
  //Constructor / Destructor
  VK_image(VK_engine* vk_engine);
  ~VK_image();

public:
  void transition_layout_image(Struct_image* image, VkImageLayout oldLayout, VkImageLayout newLayout);

private:
  VK_engine* vk_engine;
  VK_param* vk_param;
  VK_command* vk_command;
};

#endif
