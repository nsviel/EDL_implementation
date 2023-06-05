#include "VK_drawing.h"
#include "VK_cmd.h"

#include "../../VK_engine.h"
#include "../../VK_param.h"
#include "../../Pipeline/Command/VK_command.h"
#include "../../Presentation/Swapchain/VK_swapchain.h"
#include "../../Instance/Element/VK_window.h"


//Constructor / Destructor
VK_drawing::VK_drawing(VK_engine* vk_engine){
  //---------------------------

  this->vk_engine = vk_engine;
  this->vk_param = vk_engine->get_vk_param();
  this->vk_swapchain = vk_engine->get_vk_swapchain();
  this->vk_window = vk_engine->get_vk_window();
  this->vk_command = vk_engine->get_vk_command();
  this->vk_cmd = vk_engine->get_vk_cmd();

  //---------------------------
}
VK_drawing::~VK_drawing(){}

//Main function
void VK_drawing::draw_frame(){
  //---------------------------

  this->acquire_next_image(&vk_param->renderpass_scene);
  this->draw_scene();
  //this->draw_gui();

  this->submit_presentation(&vk_param->renderpass_scene);
  this->set_next_frame_ID(&vk_param->renderpass_scene);

  //---------------------------
}
void VK_drawing::draw_scene(){
  //---------------------------

  this->record_command_buffer_scene(&vk_param->renderpass_scene);
  this->submit_command(&vk_param->renderpass_scene);

  //---------------------------
}
void VK_drawing::draw_gui(){
  //---------------------------

  this->record_command_buffer_gui(&vk_param->renderpass_gui);
  this->submit_command(&vk_param->renderpass_gui);

  //---------------------------
}

//Subfunction
void VK_drawing::acquire_next_image(Struct_renderpass* renderpass){
  Frame* frame = renderpass->frame_set->get_frame_inflight();
  //---------------------------

  //Waiting for the previous frame
  vkWaitForFences(vk_param->device.device, 1, &frame->fence, VK_TRUE, UINT64_MAX);

  //Acquiring an image from the swap chain
  VkResult result = vkAcquireNextImageKHR(vk_param->device.device, vk_param->swapchain.swapchain, UINT64_MAX, frame->semaphore_presentation, VK_NULL_HANDLE, &renderpass->frame_set->frame_sawpchain_ID);
  if(result == VK_ERROR_OUT_OF_DATE_KHR){
    vk_swapchain->recreate_swapChain();
    return;
  }else if(result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR){
    throw std::runtime_error("[error] failed to acquire swap chain image!");
  }

  //Reset fence
  vkResetFences(vk_param->device.device, 1, &frame->fence);

  //Window resizing
  vk_window->check_for_resizing();
  if(result == VK_ERROR_OUT_OF_DATE_KHR){
    vk_swapchain->recreate_swapChain();
    return;
  }else if(result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR){
    throw std::runtime_error("[error] failed to acquire swap chain image!");
  }

  //---------------------------
}
void VK_drawing::set_next_frame_ID(Struct_renderpass* renderpass){
  //---------------------------

  int current_ID = renderpass->frame_set->frame_sawpchain_ID;
  current_ID = (current_ID + 1) % vk_param->instance.max_frame;
  renderpass->frame_set->frame_sawpchain_ID = current_ID;

  //---------------------------
}

//Queue submission
void VK_drawing::submit_command(Struct_renderpass* renderpass){
  Frame* frame = renderpass->frame_set->get_frame_inflight();
  //---------------------------

  VkPipelineStageFlags waitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};

  VkSubmitInfo submit_info{};
  submit_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
  submit_info.waitSemaphoreCount = 1;
  submit_info.pWaitSemaphores = &frame->semaphore_presentation;
  submit_info.pWaitDstStageMask = waitStages;
  submit_info.signalSemaphoreCount = 1;
  submit_info.pSignalSemaphores = &frame->semaphore_rendering;
  submit_info.commandBufferCount = 1;
  submit_info.pCommandBuffers = &renderpass->command_buffer;

  //Very slow operation, need as low command as possible
  VkResult result = vkQueueSubmit(vk_param->device.queue_graphics, 1, &submit_info, frame->fence);
  if(result != VK_SUCCESS){
    throw std::runtime_error("failed to submit draw command buffer!");
  }

  //---------------------------
}
void VK_drawing::submit_presentation(Struct_renderpass* renderpass){
  Frame* frame = renderpass->frame_set->get_frame_inflight();
  //---------------------------

  VkSemaphore vec_semaphore_rendering[] = {frame->semaphore_rendering};
  VkSwapchainKHR swapChains[] = {vk_param->swapchain.swapchain};
  VkPresentInfoKHR presentation_info{};
  presentation_info.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
  presentation_info.waitSemaphoreCount = 1;
  presentation_info.pWaitSemaphores = vec_semaphore_rendering;
  presentation_info.swapchainCount = 1;
  presentation_info.pSwapchains = swapChains;
  presentation_info.pImageIndices = &renderpass->frame_set->frame_sawpchain_ID;
  presentation_info.pResults = nullptr; // Optional

  VkResult result = vkQueuePresentKHR(vk_param->device.queue_presentation, &presentation_info);
  if(result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || vk_param->window.is_resized){
    vk_swapchain->recreate_swapChain();
  }else if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to present swap chain image!");
  }

  //---------------------------
}

//Command buffer record
void VK_drawing::record_command_buffer_scene(Struct_renderpass* renderpass){
  Frame* frame = renderpass->frame_set->get_frame_inflight();
  //---------------------------

  vkResetCommandBuffer(renderpass->command_buffer, 0);
  vk_command->start_command_buffer(renderpass->command_buffer);
  vk_cmd->cmd_record_scene(renderpass->command_buffer);
  vk_command->stop_command_buffer(renderpass->command_buffer);

  //---------------------------
}
void VK_drawing::record_command_buffer_gui(Struct_renderpass* renderpass){
  //---------------------------

  Frame* frame = renderpass->frame_set->get_frame_inflight();
  vkResetCommandBuffer(renderpass->command_buffer, 0);
  vk_command->start_command_buffer(renderpass->command_buffer);
  vk_cmd->cmd_record_gui(renderpass->command_buffer);
  vk_command->stop_command_buffer(renderpass->command_buffer);

  //---------------------------
}
