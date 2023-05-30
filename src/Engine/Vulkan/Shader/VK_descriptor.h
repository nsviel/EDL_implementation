#ifndef VK_DESCRIPTOR_H
#define VK_DESCRIPTOR_H

#include "../Struct/struct_uniform.h"
#include "../Struct/struct_frame.h"
#include "../Struct/struct_pipeline.h"
#include "../Struct/struct_data.h"
#include "../../../common.h"

class Engine;
class Param_vulkan;


class VK_descriptor
{
public:
  //Constructor / Destructor
  VK_descriptor(Engine* engineManager);
  ~VK_descriptor();

public:
  //Main functions
  void init_descriptor_layout();
  void cleanup();

  //Descriptor set
  void allocate_descriptor_set(vector<Struct_pipeline*> vec_pipeline);
  void allocate_descriptor_set(Struct_data* data);
  void update_descriptor_set(Struct_pipeline* pipeline);
  void update_descriptor_set(Struct_data* data);

  //Descriptor layout
  VkDescriptorSetLayout create_layout_scene();
  VkDescriptorSetLayout create_layout_glyph();
  VkDescriptorSetLayout create_layout_canvas();
  VkDescriptorSetLayout create_layout(vector<VkDescriptorSetLayoutBinding> vec_binding);
  VkDescriptorSetLayoutBinding add_descriptor_binding(VkDescriptorType type, VkShaderStageFlagBits stage, int count, int binding);

  //Descriptor pool
  void create_descriptor_pool();
  VkDescriptorPoolSize add_descriptor_type(VkDescriptorType type, int count);

  inline VkDescriptorSetLayout get_descriptor_layout_scene(){return descriptor_layout_scene;}
  inline VkDescriptorSetLayout get_descriptor_layout_glyph(){return descriptor_layout_glyph;}
  inline VkDescriptorSetLayout get_descriptor_layout_canvas(){return descriptor_layout_canvas;}

private:
  Engine* engineManager;
  Param_vulkan* param_vulkan;

  VkDescriptorPool descriptor_pool;
  VkDescriptorSetLayout descriptor_layout_scene;
  VkDescriptorSetLayout descriptor_layout_glyph;
  VkDescriptorSetLayout descriptor_layout_canvas;
  int pool_nb_uniform;
  int pool_nb_sampler;
  int pool_nb_descriptor;
};

#endif
