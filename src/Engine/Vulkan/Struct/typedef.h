#ifndef TYPEDEF_H
#define TYPEDEF_H

#include "../../../common.h"


//Memory
typedef VkMemoryPropertyFlags memory_flag;
constexpr memory_flag MEMORY_GPU = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
constexpr memory_flag MEMORY_SHARED_CPU_GPU = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;

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

//Attachment usage
typedef VkAttachmentLoadOp attachment_usage;
constexpr attachment_usage ATTACHMENT_USAGE_CLEAR = VK_ATTACHMENT_LOAD_OP_CLEAR;
constexpr attachment_usage ATTACHMENT_USAGE_CONSERVE = VK_ATTACHMENT_LOAD_OP_LOAD;

typedef VkImageLayout image_layout_usage;
constexpr image_layout_usage IMAGE_LAYOUT_EMPTY = VK_IMAGE_LAYOUT_UNDEFINED;
constexpr image_layout_usage IMAGE_LAYOUT_COLOR = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
constexpr image_layout_usage IMAGE_LAYOUT_DEPTH = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
constexpr image_layout_usage IMAGE_LAYOUT_SHADER = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
constexpr image_layout_usage IMAGE_LAYOUT_PRESENT = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;


#endif
