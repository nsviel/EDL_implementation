#ifndef VK_DATA_H
#define VK_DATA_H

#include "../../../common.h"

class Engine;
class VK_buffer;


class VK_data
{
public:
  //Constructor / Destructor
  VK_data(Engine* engineManager);
  ~VK_data();

public:
  //Main functions
  Cloud* load_model();
  std::vector<VkVertexInputAttributeDescription> description_vertex();
  std::vector<VkVertexInputBindingDescription> description_binding();

private:
  Engine* engineManager;
  VK_buffer* vk_buffer;
};

#endif
