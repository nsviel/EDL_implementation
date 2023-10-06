#ifndef TYPEDEF_H
#define TYPEDEF_H

#include <Specific/common.h>


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
typedef VkAttachmentLoadOp load_operation;
constexpr load_operation ATTACHMENT_LOADOP_CLEAR = VK_ATTACHMENT_LOAD_OP_CLEAR;
constexpr load_operation ATTACHMENT_LOADOP_LOAD = VK_ATTACHMENT_LOAD_OP_LOAD;

typedef VkAttachmentStoreOp store_operation;
constexpr store_operation ATTACHMENT_STOREOP_NOTHING = VK_ATTACHMENT_STORE_OP_DONT_CARE;
constexpr store_operation ATTACHMENT_STOREOP_STORE = VK_ATTACHMENT_STORE_OP_STORE;

//Image layout
typedef VkImageLayout image_layout;
constexpr image_layout IMAGE_LAYOUT_EMPTY = VK_IMAGE_LAYOUT_UNDEFINED;
constexpr image_layout IMAGE_LAYOUT_COLOR_ATTACHMENT = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
constexpr image_layout IMAGE_LAYOUT_DEPTH_ATTACHMENT = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
constexpr image_layout IMAGE_LAYOUT_DEPTH_READONLY = VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL;
constexpr image_layout IMAGE_LAYOUT_SHADER_READONLY = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
constexpr image_layout IMAGE_LAYOUT_TRANSFER_DST = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
constexpr image_layout IMAGE_LAYOUT_PRESENT = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

//image usage
typedef VkImageUsageFlags image_usage;
constexpr image_usage IMAGE_USAGE_DEPTH = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;
constexpr image_usage IMAGE_USAGE_TRANSFERT = VK_IMAGE_USAGE_TRANSFER_DST_BIT;
constexpr image_usage IMAGE_USAGE_SAMPLER = VK_IMAGE_USAGE_SAMPLED_BIT;
constexpr image_usage IMAGE_USAGE_ATTACHMENT = VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT;


#endif
