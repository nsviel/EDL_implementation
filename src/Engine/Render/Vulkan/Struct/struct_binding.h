#ifndef STRUCT_BINDING_H
#define STRUCT_BINDING_H

#include "typedef.h"
#include <Specific/common.h>

//Consistent attribut binding:
//  -position -> 0
//  -color -> 1
//  -uv -> 2
//  -normal -> 3
//  -depth -> 4
//  -uniform -> 5


//Binding requirement -> Name, Type size, binding, desriptor type, shader stage
typedef std::vector<std::tuple<std::string, std::size_t, int, VkDescriptorType, VkShaderStageFlagBits>> vec_descriptor_required;
typedef std::tuple<std::string, std::size_t, int, VkDescriptorType, VkShaderStageFlagBits> descriptor_required;

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
  size_t size;
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
  VkDescriptorType type;

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

  //Binding description
  vec_descriptor_required vec_required_binding;
  Struct_descriptor descriptor;

  //Binding elements
  vector<Struct_pushcst*> vec_pushcst;
  vector<Struct_uniform*> vec_uniform;
  vector<Struct_sampler*> vec_sampler;

  //---------------------------
};


#endif
