#ifndef STRUCT_DESCRIPTOR_H
#define STRUCT_DESCRIPTOR_H

#include <string>
#include <vector>
#include <vulkan/vulkan.h>


struct Struct_descriptor{
  VkDescriptorPool descriptor_pool;
  VkDescriptorSetLayout descriptor_layout;
  std::vector<VkDescriptorSet> descriptor_set;
};


#endif
