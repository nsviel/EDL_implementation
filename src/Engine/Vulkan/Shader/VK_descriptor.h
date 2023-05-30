#ifndef VK_DESCRIPTOR_H
#define VK_DESCRIPTOR_H

#include "../Struct/struct_uniform.h"
#include "../Struct/struct_frame.h"
#include "../Struct/struct_pipeline.h"
#include "../../../common.h"

class Engine;
class Param_vulkan;
class VK_device;
class VK_texture;
class VK_frame;


class VK_descriptor
{
public:
  //Constructor / Destructor
  VK_descriptor(Engine* engineManager);
  ~VK_descriptor();

public:
  //Main functions
  void cleanup();

  //Descriptor set
  void allocate_descriptor_set(vector<Struct_pipeline*> vec_pipeline);
  void configure_descriptor_set(Struct_pipeline* pipeline);

  //Descriptor layout
  VkDescriptorSetLayout create_layout_scene();
  VkDescriptorSetLayout create_layout_glyph();
  VkDescriptorSetLayout create_layout_canvas();
  VkDescriptorSetLayout create_layout(vector<VkDescriptorSetLayoutBinding> vec_binding);
  VkDescriptorSetLayoutBinding add_descriptor_binding(VkDescriptorType type, VkShaderStageFlagBits stage, int count, int binding);

  //Descriptor pool
  void create_descriptor_pool();
  VkDescriptorPoolSize add_descriptor_type(VkDescriptorType type, int count);

private:
  Engine* engineManager;
  Param_vulkan* param_vulkan;
  VK_device* vk_device;
  VK_frame* vk_frame;
  VK_texture* vk_texture;

  VkDescriptorPool descriptor_pool;
  int pool_nb_uniform;
  int pool_nb_sampler;
};

#endif
