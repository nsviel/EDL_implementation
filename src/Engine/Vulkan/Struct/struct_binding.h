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

  vec_nameTypeBindingTypeStage vec_required_binding;
  vector<Struct_uniform*> vec_uniform;
  vector<Struct_pushcst*> vec_pushcst;
  Struct_descriptor descriptor;

  //---------------------------
};


#endif
