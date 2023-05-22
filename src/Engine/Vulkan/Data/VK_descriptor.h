#ifndef VK_DESCRIPTOR_H
#define VK_DESCRIPTOR_H

#include "../Struct/struct_mvp.h"
#include "../../../common.h"

class Engine;
class Param_vulkan;
class VK_device;
class VK_image;


class VK_descriptor
{
public:
  //Constructor / Destructor
  VK_descriptor(Engine* engineManager);
  ~VK_descriptor();

public:
  //Main functions
  void init_descriptor();
  void fill_vec_frame(vector<VkDescriptorSet> descriptor_set);
  void cleanup();

  //Subfunctions
  void create_descriptor_set_layout();
  void create_descriptor_pool();
  void create_descriptor_set();

  //Update function
  void update_descriptor_set();
  void update_descriptor_set_texture(Object* object);

  inline VkDescriptorSetLayout get_descriptor_layout(){return descriptor_layout;}

private:
  Engine* engineManager;
  Param_vulkan* param_vulkan;
  VK_device* vk_device;
  VK_image* vk_image;

  VkDescriptorPool descriptor_pool;
  VkDescriptorSetLayout descriptor_layout;
};

#endif
