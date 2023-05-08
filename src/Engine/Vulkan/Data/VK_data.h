#ifndef VK_DATA_H
#define VK_DATA_H

#include "../../../common.h"

class Engine;
class VK_device;
class VK_buffer;
class VK_texture;


class VK_data
{
public:
  //Constructor / Destructor
  VK_data(Engine* engineManager);
  ~VK_data();

public:
  //Main functions
  Mesh* load_model();
  std::vector<VkVertexInputAttributeDescription> description_vertex();
  std::vector<VkVertexInputBindingDescription> description_binding();
  void cleanup();

  inline void set_list_data(std::list<Object*> value){this->list_data = value;}
  inline std::list<Object*> get_list_data(){return list_data;}

private:
  Engine* engineManager;
  VK_device* vk_device;
  VK_buffer* vk_buffer;
  VK_texture* vk_texture;

  std::list<Object*> list_data;
};

#endif
