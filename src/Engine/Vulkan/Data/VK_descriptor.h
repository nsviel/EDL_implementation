#ifndef VK_DESCRIPTOR_H
#define VK_DESCRIPTOR_H

#include "../Struct/struct_mvp.h"
#include "../../../common.h"

class Engine;
class Param_engine;
class VK_device;


class VK_descriptor
{
public:
  //Constructor / Destructor
  VK_descriptor(Engine* engineManager);
  ~VK_descriptor();

public:
  //Main functions
  void init_descriptor();
  void cleanup();

  //Subfunctions
  void create_descriptor_set_layout();
  void create_descriptor_pool();
  void create_descriptor_set();

  //Update function
  void update_descriptor_set();
  void update_descriptor_set_texture(Object* object);

  inline VkDescriptorSetLayout get_descriptorSetLayout(){return descriptor_layout;}
  inline std::vector<VkDescriptorSet> get_descriptorSets(){return descriptor_set;}

private:
  Engine* engineManager;
  Param_engine* param_engine;
  VK_device* vk_device;

  VkDescriptorPool descriptor_pool;
  VkDescriptorSetLayout descriptor_layout;
  std::vector<VkDescriptorSet> descriptor_set;
};

#endif
