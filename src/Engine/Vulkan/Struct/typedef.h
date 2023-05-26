#ifndef TYPEDEF_H
#define TYPEDEF_H

#include "../../../common.h"


//Memory
typedef VkMemoryPropertyFlags memory_flag;
constexpr memory_flag MEMORY_GPU = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
constexpr memory_flag MEMORY_CPU_VISIBLE_GPU = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;

//Descriptor type
typedef VkDescriptorType descriptor_type;
constexpr descriptor_type TYPE_UNIFORM = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
constexpr descriptor_type TYPE_SAMPLER = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;

//Stage flag
typedef VkShaderStageFlagBits shader_stage;
constexpr shader_stage STAGE_VS = VK_SHADER_STAGE_VERTEX_BIT;
constexpr shader_stage STAGE_FS = VK_SHADER_STAGE_FRAGMENT_BIT;

//Pipeline
typedef VkPipelineBindPoint pipeline_point;
constexpr pipeline_point PIPELINE_GRAPHICS = VK_PIPELINE_BIND_POINT_GRAPHICS;

//Buffer usage
typedef VkBufferUsageFlags buffer_usage;
constexpr buffer_usage BUFFER_USAGE_SRC = VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
constexpr buffer_usage BUFFER_USAGE_DST = VK_BUFFER_USAGE_TRANSFER_DST_BIT;
constexpr buffer_usage BUFFER_USAGE_DST_VERTEX = VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;

//Specific type
typedef vector<std::pair<std::string, std::string>> vec_name_type;
typedef std::pair<std::string, std::string> name_type;


#endif
