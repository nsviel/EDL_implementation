#include "VK_submit.h"
#include "../Drawing/VK_cmd.h"
#include "../Pipeline/VK_pipeline.h"
#include "../VK_engine.h"
#include "../VK_param.h"
#include "../Command/VK_command.h"
#include "../Presentation/VK_swapchain.h"
#include "../Window/VK_surface.h"
#include "../Presentation/VK_canvas.h"
#include "../Binding/VK_descriptor.h"


//Constructor / Destructor
VK_submit::VK_submit(VK_engine* vk_engine){
  //---------------------------

  this->vk_engine = vk_engine;
  this->vk_param = vk_engine->get_vk_param();
  this->vk_swapchain = vk_engine->get_vk_swapchain();
  this->vk_surface = vk_engine->get_vk_surface();
  this->vk_command = vk_engine->get_vk_command();
  this->vk_cmd = vk_engine->get_vk_cmd();
  this->vk_descriptor = vk_engine->get_vk_descriptor();

  //---------------------------
}
VK_submit::~VK_submit(){}

//Main function
void VK_submit::acquire_next_image(Struct_swapchain* swapchain){
  Frame* frame_inflight = swapchain->get_frame_inflight();
  //---------------------------

  //Wait and reset fence
  vkWaitForFences(vk_param->device.device, 1, &frame_inflight->fence, VK_TRUE, UINT64_MAX);
  vkResetFences(vk_param->device.device, 1, &frame_inflight->fence);

  //Acquiring an image from the swap chain
  VkResult result = vkAcquireNextImageKHR(vk_param->device.device, swapchain->swapchain, UINT64_MAX, frame_inflight->semaphore_image_ready, VK_NULL_HANDLE, &swapchain->frame_current_ID);
  if(result == VK_ERROR_OUT_OF_DATE_KHR){
    vk_swapchain->recreate_swapChain();
    return;
  }else if(result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR){
    throw std::runtime_error("[error] failed to acquire swap chain image!");
  }


  //Window resizing
  vk_surface->check_for_resizing();
  if(result == VK_ERROR_OUT_OF_DATE_KHR){
    vk_swapchain->recreate_swapChain();
    return;
  }else if(result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR){
    throw std::runtime_error("[error] failed to acquire swap chain image!");
  }

  //---------------------------
}
void VK_submit::set_next_frame_ID(Struct_swapchain* swapchain){
  //---------------------------

  int current_ID = swapchain->frame_current_ID;
  current_ID = (current_ID + 1) % vk_param->instance.max_frame_inflight;
  swapchain->frame_current_ID = current_ID;

  //---------------------------
}

//Queue submission
void VK_submit::submit_graphics_command(Struct_submit_command* command){
  //---------------------------

  VkSubmitInfo submit_info{};
  submit_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
  submit_info.waitSemaphoreCount = 1;
  submit_info.pWaitSemaphores = &command->semaphore_to_wait;
  submit_info.pWaitDstStageMask = &command->wait_stage;
  submit_info.signalSemaphoreCount = 1;
  submit_info.pSignalSemaphores = &command->semaphore_to_run;
  submit_info.commandBufferCount = 1;
  submit_info.pCommandBuffers = &command->command_buffer;

  //Very slow operation, need as low command as possible
  VkResult result = vkQueueSubmit(vk_param->device.queue_graphics, 1, &submit_info, command->fence);
  if(result != VK_SUCCESS){
    throw std::runtime_error("failed to submit draw command buffer!");
  }

  //---------------------------
}
void VK_submit::submit_graphics_command(Struct_renderpass* renderpass){
  //---------------------------

  Frame* frame_swap = vk_param->swapchain.get_frame_inflight();
  Struct_submit_command command;
  command.command_buffer = renderpass->command_buffer;
  command.semaphore_to_wait = renderpass->semaphore_to_wait;
  command.semaphore_to_run = renderpass->semaphore_to_run;
  command.fence = renderpass->fence;
  command.wait_stage = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;

  VkSubmitInfo submit_info{};
  submit_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
  submit_info.waitSemaphoreCount = 1;
  submit_info.pWaitSemaphores = &command.semaphore_to_wait;
  submit_info.pWaitDstStageMask = &command.wait_stage;
  submit_info.signalSemaphoreCount = 1;
  submit_info.pSignalSemaphores = &command.semaphore_to_run;
  submit_info.commandBufferCount = 1;
  submit_info.pCommandBuffers = &command.command_buffer;

  //Very slow operation, need as low command as possible
  VkResult result = vkQueueSubmit(vk_param->device.queue_graphics, 1, &submit_info, command.fence);
  if(result != VK_SUCCESS){
    throw std::runtime_error("failed to submit draw command buffer!");
  }

  //---------------------------
}
void VK_submit::submit_graphics_commands(Struct_submit_commands* commands){
  //---------------------------

  VkSubmitInfo submit_info{};
  submit_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
  submit_info.waitSemaphoreCount = commands->vec_semaphore_to_wait.size();
  submit_info.pWaitSemaphores = commands->vec_semaphore_to_wait.data();
  submit_info.pWaitDstStageMask = commands->vec_wait_stage.data();
  submit_info.signalSemaphoreCount = commands->vec_semaphore_to_run.size();
  submit_info.pSignalSemaphores = commands->vec_semaphore_to_run.data();
  submit_info.commandBufferCount = commands->vec_command_buffer.size();
  submit_info.pCommandBuffers = commands->vec_command_buffer.data();

  //Very slow operation, need as low command as possible
  VkResult result = vkQueueSubmit(vk_param->device.queue_graphics, 1, &submit_info, commands->fence);
  if(result != VK_SUCCESS){
    throw std::runtime_error("failed to submit draw command buffer!");
  }

  //---------------------------
}
void VK_submit::submit_presentation(Struct_swapchain* swapchain){
  Frame* frame_inflight = swapchain->get_frame_inflight();
  //---------------------------

  VkPresentInfoKHR presentation_info{};
  presentation_info.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
  presentation_info.waitSemaphoreCount = 1;
  presentation_info.pWaitSemaphores = &frame_inflight->semaphore_ui_ready;
  presentation_info.swapchainCount = 1;
  presentation_info.pSwapchains = &swapchain->swapchain;
  presentation_info.pImageIndices = &swapchain->frame_current_ID;
  presentation_info.pResults = nullptr; // Optional

  VkResult result = vkQueuePresentKHR(vk_param->device.queue_presentation, &presentation_info);
  if(result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || vk_param->window.is_resized){
    vk_swapchain->recreate_swapChain();
  }else if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to present swap chain image!");
  }

  //---------------------------
}
