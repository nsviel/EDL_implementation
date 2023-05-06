#ifndef VK_DESCRIPTOR_H
#define VK_DESCRIPTOR_H

#include <vulkan/vulkan.h>

#include "../../../common.h"

class Engine;
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

  //Subfunctions
  void create_descriptor_set_layout();
  void create_descriptor_pool();
  void create_descriptor_set();
  void cleanup();

  inline VkDescriptorSetLayout get_descriptorSetLayout(){return descriptor_layout;}
  inline std::vector<VkDescriptorSet> get_descriptorSets(){return descriptor_set;}

private:
  Engine* engineManager;
  VK_device* vk_device;

  VkDescriptorPool descriptor_pool;
  VkDescriptorSetLayout descriptor_layout;
  std::vector<VkDescriptorSet> descriptor_set;
};

#endif
