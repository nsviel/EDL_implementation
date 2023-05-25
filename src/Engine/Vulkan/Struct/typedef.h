#ifndef TYPEDEF_H
#define TYPEDEF_H

#include <vulkan/vulkan.h>


//Memory
typedef VkMemoryPropertyFlags memory_flag;
constexpr memory_flag memory_gpu = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
constexpr memory_flag memory_cpu_visible_gpu = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;

//Descriptor type
typedef VkDescriptorType descriptor_type;
constexpr descriptor_type uniform = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
constexpr descriptor_type sampler = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;

//Stage flag
typedef VkShaderStageFlagBits shader_stage;
constexpr shader_stage stage_vs = VK_SHADER_STAGE_VERTEX_BIT;
constexpr shader_stage stage_fs = VK_SHADER_STAGE_FRAGMENT_BIT;



#endif
