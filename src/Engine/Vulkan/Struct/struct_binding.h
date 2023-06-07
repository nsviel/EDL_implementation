#ifndef STRUCT_BINDING_H
#define STRUCT_BINDING_H

#include "typedef.h"
#include "../../../common.h"

//Binding requirement
typedef std::vector<std::tuple<std::string, std::string, int, VkDescriptorType, VkShaderStageFlagBits>> vec_nameTypeBindingTypeStage;
typedef std::tuple<std::string, std::string, int, VkDescriptorType, VkShaderStageFlagBits> nameTypeBindingTypeStage;

//Structures
struct Struct_descriptor{
  //---------------------------

  VkDescriptorSetLayout layout;
  VkDescriptorSet set;

  //---------------------------
};

struct Struct_uniform{
  //---------------------------

  std::string name;
  int binding;
  VkBuffer buffer;
  VkDeviceMemory mem;
  void* mapped;

  //---------------------------
};

struct Struct_sampler{
  //---------------------------

  std::string name;
  int binding;

  //---------------------------
};

struct Struct_pushcst{
  //---------------------------

  std::string name;
  int binding;
  VkShaderStageFlagBits stage;

  //---------------------------
};

struct Struct_binding{
  //---------------------------

  bool need_update = true;

  //Binding description
  vec_nameTypeBindingTypeStage vec_required_binding;
  vector<VkWriteDescriptorSet> vec_descriptor_write;
  vector<VkDescriptorBufferInfo> vec_descriptor_buffer_info;
  vector<VkDescriptorImageInfo> vec_descriptor_image_info;
  Struct_descriptor descriptor;

  //Binding elements
  vector<Struct_pushcst*> vec_pushcst;
  vector<Struct_uniform*> vec_uniform;
  vector<Struct_sampler*> vec_sampler;
  list<Struct_image*> list_texture;

  //---------------------------
};


#endif
