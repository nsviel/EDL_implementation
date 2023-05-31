#ifndef VK_DESCRIPTOR_H
#define VK_DESCRIPTOR_H

#include "../Struct/struct_binding.h"
#include "../Struct/struct_frame.h"
#include "../Struct/struct_pipeline.h"
#include "../Struct/struct_data.h"
#include "../../../common.h"

class VK_engine;
class VK_param;


class VK_descriptor
{
public:
  //Constructor / Destructor
  VK_descriptor(VK_engine* vk_engine);
  ~VK_descriptor();

public:
  //Main functions
  void cleanup();

  //Descriptor set
  void allocate_descriptor_set(vector<VkDescriptorSetLayout>& vec_layout, vector<VkDescriptorSet>& vec_descriptor_set);
  void allocate_descriptor_set(VkDescriptorSetLayout& layout, VkDescriptorSet& descriptor_set);
  void update_descriptor_set(Struct_binding& binding);

  //Descriptor layout
  VkDescriptorSetLayout create_layout_from_required(vec_nameTypeBindingTypeStage& vec_required_binding);
  VkDescriptorSetLayout create_layout(vector<VkDescriptorSetLayoutBinding> vec_binding);
  VkDescriptorSetLayoutBinding add_descriptor_binding(VkDescriptorType type, VkShaderStageFlagBits stage, int count, int binding);

  //Descriptor pool
  void create_descriptor_pool();
  VkDescriptorPoolSize add_descriptor_type(VkDescriptorType type, int count);

private:
  VK_engine* vk_engine;
  VK_param* vk_param;

  VkDescriptorPool descriptor_pool;
  int pool_nb_uniform;
  int pool_nb_sampler;
  int pool_nb_descriptor;
};

#endif
