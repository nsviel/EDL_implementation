#ifndef VK_DATA_H
#define VK_DATA_H

#include "../../../common.h"

class Engine_vulkan;
class VK_buffer;


class VK_data
{
public:
  //Constructor / Destructor
  VK_data(Engine_vulkan* engine_vulkan);
  ~VK_data();

public:
  //Main functions
  Cloud* load_model();
  std::vector<VkVertexInputAttributeDescription> vertex_attribute();

private:
  Engine_vulkan* engine_vulkan;
  VK_buffer* vk_buffer;
};

#endif
