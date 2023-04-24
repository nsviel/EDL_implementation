#ifndef VK_DESCRIPTOR_H
#define VK_DESCRIPTOR_H

#include <vulkan/vulkan.h>

#include "../../common.h"

class Engine_vulkan;
class VK_device;


class VK_descriptor
{
public:
  //Constructor / Destructor
  VK_descriptor(Engine_vulkan* engine_vulkan);
  ~VK_descriptor();

public:
  //Main functions
  void create_descriptorSet_layout();
  void create_descriptor_pool();
  void create_descriptor_sets();
  void cleanup();

  inline VkDescriptorSetLayout get_descriptorSetLayout(){return descriptorSetLayout;}
  inline std::vector<VkDescriptorSet> get_descriptorSets(){return descriptorSets;}

private:
  Engine_vulkan* engine_vulkan;
  VK_device* vk_device;

  VkDescriptorPool descriptorPool;
  VkDescriptorSetLayout descriptorSetLayout;
  std::vector<VkDescriptorSet> descriptorSets;
};

#endif
