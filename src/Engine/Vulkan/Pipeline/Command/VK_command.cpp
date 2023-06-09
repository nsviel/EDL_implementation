#include "VK_command.h"
#include "../Drawing/VK_cmd.h"

#include "../../VK_param.h"
#include "../../VK_engine.h"

#include "../../Instance/Element/VK_gui.h"
#include "../../Instance/Element/VK_window.h"
#include "../../Instance/Device/VK_device.h"
#include "../../Instance/Device/VK_physical_device.h"

#include "../../Pipeline/Renderpass/VK_renderpass.h"
#include "../../Pipeline/Pipeline/VK_pipeline.h"

#include "../../Data/VK_buffer.h"
#include "../../Data/VK_data.h"

#include "../../Presentation/Swapchain/VK_frame.h"
#include "../../Presentation/Camera/VK_viewport.h"
#include "../../Presentation/Camera/VK_camera.h"

#include "../../Rendering/Render/VK_canvas.h"
#include "../../Rendering/Binding/VK_descriptor.h"

#include "../../../Param_engine.h"


//Constructor / Destructor
VK_command::VK_command(VK_engine* vk_engine){
  //---------------------------

  this->param_engine = vk_engine->get_param_engine();
  this->vk_engine = vk_engine;
  this->vk_param = vk_engine->get_vk_param();
  this->vk_renderpass = vk_engine->get_vk_renderpass();
  this->vk_physical_device = vk_engine->get_vk_physical_device();
  this->vk_cmd = vk_engine->get_vk_cmd();
  this->vk_pipeline = vk_engine->get_vk_pipeline();
  this->vk_descriptor = vk_engine->get_vk_descriptor();

  //---------------------------
}
VK_command::~VK_command(){}

//Command pool
void VK_command::create_command_pool(){
  //---------------------------

  int family_graphics = vk_physical_device->find_queue_family_graphics(vk_param->device.physical_device);

  //Command pool info
  VkCommandPoolCreateInfo poolInfo{};
  poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
  poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
  poolInfo.queueFamilyIndex = family_graphics;

  //Command pool creation
  VkResult result = vkCreateCommandPool(vk_param->device.device, &poolInfo, nullptr, &command_pool);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to create command pool!");
  }

  //---------------------------
}
void VK_command::clean_command_pool(){
  //---------------------------

  vkDestroyCommandPool(vk_param->device.device, command_pool, nullptr);

  //---------------------------
}

//Descriptor
void VK_command::update_uniform(Struct_renderpass* renderpass, string pipeline_name){
  //---------------------------

  Struct_pipeline* pipeline = vk_pipeline->get_pipeline_byName(renderpass, pipeline_name);
  vk_descriptor->update_descriptor_uniform(&pipeline->binding);

  //---------------------------
}
void VK_command::update_sampler(Struct_renderpass* renderpass, string pipeline_name, Struct_image* image){
  //---------------------------

  list<Struct_image*> vec_image;
  vec_image.push_back(image);
  Struct_pipeline* pipeline = vk_pipeline->get_pipeline_byName(renderpass, pipeline_name);
  vk_descriptor->update_descriptor_sampler(&pipeline->binding, vec_image);

  //---------------------------
}

//Command buffer
void VK_command::allocate_command_buffer(Struct_renderpass* renderpass){
  //---------------------------

  //Command buffer allocation
  VkCommandBufferAllocateInfo allocInfo{};
  allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
  allocInfo.commandPool = command_pool;
  allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
  allocInfo.commandBufferCount = 1;

  VkCommandBuffer command_buffer;
  VkResult result = vkAllocateCommandBuffers(vk_param->device.device, &allocInfo, &command_buffer);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to allocate command buffers!");
  }

  renderpass->command_buffer = command_buffer;

  //---------------------------
}
void VK_command::start_command_buffer(Struct_renderpass* renderpass){
  //---------------------------

  VkCommandBufferBeginInfo begin_info{};
  begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
  begin_info.flags = 0;

  VkResult result = vkBeginCommandBuffer(renderpass->command_buffer, &begin_info);
  if(result != VK_SUCCESS){
    throw std::runtime_error("failed to begin recording command buffer!");
  }

  //---------------------------
}
void VK_command::stop_command_buffer(Struct_renderpass* renderpass){
  //---------------------------

  VkResult result = vkEndCommandBuffer(renderpass->command_buffer);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to record command buffer!");
  }

  //---------------------------
}

//Render pass
void VK_command::start_render_pass(Struct_renderpass* renderpass, Frame* frame){
  //---------------------------

  std::array<VkClearValue, 2> clear_value{};
  clear_value[0].color = {{
    param_engine->background_color.x,
    param_engine->background_color.y,
    param_engine->background_color.z,
    param_engine->background_color.w}};
  clear_value[1].depthStencil = {1.0f, 0};

  VkRenderPassBeginInfo renderpass_info{};
  renderpass_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
  renderpass_info.renderPass = renderpass->renderpass;
  renderpass_info.framebuffer = frame->fbo;
  renderpass_info.renderArea.offset = {0, 0};
  renderpass_info.renderArea.extent = vk_param->window.extent;
  renderpass_info.clearValueCount = static_cast<uint32_t>(clear_value.size());
  renderpass_info.pClearValues = clear_value.data();

  vkCmdBeginRenderPass(renderpass->command_buffer, &renderpass_info, VK_SUBPASS_CONTENTS_INLINE);

  //---------------------------
}
void VK_command::stop_render_pass(Struct_renderpass* renderpass){
  //---------------------------

  vkCmdEndRenderPass(renderpass->command_buffer);

  //---------------------------
}

//Image layout transition
void VK_command::image_layout_transition(VkCommandBuffer command_buffer, Struct_image* image, VkImageLayout old_layout, VkImageLayout new_layout){
  //---------------------------

  VkImageMemoryBarrier barrier{};
  barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
  barrier.oldLayout = old_layout;
  barrier.newLayout = new_layout;
  barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
  barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
  barrier.image = image->image;
  barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
  barrier.subresourceRange.baseMipLevel = 0;
  barrier.subresourceRange.levelCount = 1;
  barrier.subresourceRange.baseArrayLayer = 0;
  barrier.subresourceRange.layerCount = 1;

  VkPipelineStageFlags sourceStage;
  VkPipelineStageFlags destinationStage;

  if(old_layout == VK_IMAGE_LAYOUT_UNDEFINED && new_layout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL){
    barrier.srcAccessMask = 0;
    barrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;

    sourceStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
    destinationStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
  }else if(old_layout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL && new_layout == VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL){
    barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
    barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

    sourceStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
    destinationStage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
  }else{
    throw std::invalid_argument("unsupported layout transition!");
  }

  vkCmdPipelineBarrier(command_buffer, sourceStage, destinationStage, 0, 0, nullptr, 0, nullptr, 1, &barrier);

  //---------------------------
}
void VK_command::image_layout_transition_single(Struct_image* image, VkImageLayout old_layout, VkImageLayout new_layout){
  VK_command* vk_command = vk_engine->get_vk_command();
  //---------------------------

  VkCommandBuffer command_buffer = singletime_command_buffer_begin();
  this->image_layout_transition(command_buffer, image, old_layout, new_layout);
  this->singletime_command_buffer_end(command_buffer);

  //---------------------------
}

//Single time command
VkCommandBuffer VK_command::singletime_command_buffer_begin(){
  //---------------------------

  VkCommandBufferAllocateInfo allocInfo{};
  allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
  allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
  allocInfo.commandPool = command_pool;
  allocInfo.commandBufferCount = 1;

  VkCommandBuffer command_buffer;
  vkAllocateCommandBuffers(vk_param->device.device, &allocInfo, &command_buffer);

  VkCommandBufferBeginInfo begin_info{};
  begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
  begin_info.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

  vkBeginCommandBuffer(command_buffer, &begin_info);

  //---------------------------
  return command_buffer;
}
void VK_command::singletime_command_buffer_end(VkCommandBuffer command_buffer){
  //---------------------------

  vkEndCommandBuffer(command_buffer);

  VkSubmitInfo submitInfo{};
  submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
  submitInfo.commandBufferCount = 1;
  submitInfo.pCommandBuffers = &command_buffer;

  vkQueueSubmit(vk_param->device.queue_graphics, 1, &submitInfo, VK_NULL_HANDLE);
  vkQueueWaitIdle(vk_param->device.queue_graphics);

  vkFreeCommandBuffers(vk_param->device.device, command_pool, 1, &command_buffer);

  //---------------------------
}
