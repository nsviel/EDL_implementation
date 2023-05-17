#include "VK_command.h"

#include "../Param_vulkan.h"
#include "../Engine.h"
#include "../Instance/VK_gui.h"
#include "../Instance/VK_window.h"
#include "../Pipeline/VK_renderpass.h"
#include "../Pipeline/VK_pipeline.h"
#include "../Device/VK_device.h"
#include "../Device/VK_physical_device.h"
#include "../Data/VK_buffer.h"
#include "../Data/VK_data.h"
#include "../Swapchain/VK_image.h"
#include "../Camera/VK_viewport.h"
#include "../Camera/VK_camera.h"
#include "../Shader/VK_uniform.h"

#include "../../Param_engine.h"


//Constructor / Destructor
VK_command::VK_command(Engine* engineManager){
  //---------------------------

  this->engineManager = engineManager;
  this->param_engine = engineManager->get_param_engine();
  this->param_vulkan = engineManager->get_param_vulkan();
  this->vk_device = engineManager->get_vk_device();
  this->vk_renderpass = engineManager->get_vk_renderpass();
  this->vk_pipeline = engineManager->get_vk_pipeline();
  this->vk_viewport = engineManager->get_vk_viewport();
  this->vk_window = engineManager->get_vk_window();
  this->vk_buffer = engineManager->get_vk_buffer();
  this->vk_camera = engineManager->get_vk_camera();
  this->vk_physical_device = engineManager->get_vk_physical_device();
  this->vk_image = engineManager->get_vk_image();

  //---------------------------
}
VK_command::~VK_command(){}

//Main function
void VK_command::create_command_pool(){
  VkPhysicalDevice physical_device = vk_physical_device->get_physical_device();
  VkDevice device = vk_device->get_device();
  //---------------------------

  int family_graphics = vk_physical_device->find_queue_family_graphics(physical_device);

  //Command pool info
  VkCommandPoolCreateInfo poolInfo{};
  poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
  poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
  poolInfo.queueFamilyIndex = family_graphics;

  //Command pool creation
  VkResult result = vkCreateCommandPool(device, &poolInfo, nullptr, &command_pool);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to create command pool!");
  }

  //---------------------------
}
void VK_command::create_command_buffers(){
  VkDevice device = vk_device->get_device();
  //---------------------------

  //One command buffer per frame
  vector<VkCommandBuffer> command_buffer_vec;
  command_buffer_vec.resize(param_vulkan->max_frame);

  //Command buffer allocation
  VkCommandBufferAllocateInfo allocInfo{};
  allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
  allocInfo.commandPool = command_pool;
  allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
  allocInfo.commandBufferCount = (uint32_t) command_buffer_vec.size();

  VkResult result = vkAllocateCommandBuffers(device, &allocInfo, command_buffer_vec.data());
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to allocate command buffers!");
  }

  vector<Frame*> vec_frame = vk_image->get_vec_frame();
  for(int i=0; i<vec_frame.size(); i++){
    Frame* frame = vec_frame[i];
    frame->command_buffer = command_buffer_vec[i];
  }

  //---------------------------
}
void VK_command::cleanup(){
  VkDevice device = vk_device->get_device();
  //---------------------------

  vkDestroyCommandPool(device, command_pool, nullptr);

  //---------------------------
}

//Render pass
void VK_command::record_command_buffer(VkCommandBuffer command_buffer, uint32_t imageIndex, uint32_t current_frame){
  VkExtent2D swapchain_extent = vk_physical_device->get_extent();
  VkRenderPass renderPass = vk_renderpass->get_renderPass();
  //---------------------------

  vector<Image*> vec_image_obj = vk_image->get_vec_image();

  VkCommandBufferBeginInfo beginInfo{};
  beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

  VkResult result = vkBeginCommandBuffer(command_buffer, &beginInfo);
  if(result != VK_SUCCESS){
    throw std::runtime_error("failed to begin recording command buffer!");
  }

  //Starting a render pass
  std::array<VkClearValue, 2> clearValues{};
  clearValues[0].color = {{
    param_engine->background_color.x,
    param_engine->background_color.y,
    param_engine->background_color.z,
    param_engine->background_color.w}};
  clearValues[1].depthStencil = {1.0f, 0};

  VkRenderPassBeginInfo renderPassInfo{};
  renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
  renderPassInfo.renderPass = renderPass;
  renderPassInfo.framebuffer = vec_image_obj[imageIndex]->fbo_vec[0];
  renderPassInfo.renderArea.offset = {0, 0};
  renderPassInfo.renderArea.extent = swapchain_extent;
  renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
  renderPassInfo.pClearValues = clearValues.data();

  this->compute_render_pass(command_buffer, renderPassInfo, current_frame);

  //---------------------------
}
void VK_command::compute_render_pass(VkCommandBuffer command_buffer, VkRenderPassBeginInfo renderPassInfo, uint32_t current_frame){
  //---------------------------

  vkCmdBeginRenderPass(command_buffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

  this->command_viewport(command_buffer);
  this->command_drawing_line(command_buffer, current_frame);
  this->command_drawing_point(command_buffer, current_frame);
  this->command_gui(command_buffer);

  //End render pass
  vkCmdEndRenderPass(command_buffer);
  VkResult result = vkEndCommandBuffer(command_buffer);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to record command buffer!");
  }

  //---------------------------
}

//Specific commands
void VK_command::command_gui(VkCommandBuffer command_buffer){
  VK_gui* vk_gui = engineManager->get_vk_gui();
  //---------------------------

  vk_gui->command_gui(command_buffer);

  //---------------------------
}
void VK_command::command_viewport(VkCommandBuffer command_buffer){
  VkExtent2D swapchain_extent = vk_physical_device->get_extent();
  //---------------------------

  vk_viewport->update_viewport(swapchain_extent);

  VkViewport viewport = vk_viewport->get_viewport();
  VkRect2D scissor = vk_viewport->get_scissor();

  vkCmdSetViewport(command_buffer, 0, 1, &viewport);
  vkCmdSetScissor(command_buffer, 0, 1, &scissor);

  //---------------------------
}
void VK_command::command_drawing_point(VkCommandBuffer command_buffer, uint32_t current_frame){
  VK_data* vk_data = engineManager->get_vk_data();
  //---------------------------

  vector<Frame*> vec_frame = vk_image->get_vec_frame();
  Frame* frame = vec_frame[current_frame];

  //Bind pipeline
  VkPipeline pipeline = vk_pipeline->get_pipeline_point();
  VkPipelineLayout pipeline_layout = vk_pipeline->get_pipeline_layout_point();
  vkCmdBindPipeline(command_buffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline);

  //Bind descriptor
  list<Object*> list_data = vk_data->get_list_data();
  if(list_data.size() != 0){
    vkCmdBindDescriptorSets(command_buffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline_layout, 0, 1, &frame->descriptor_set, 0, nullptr);
  }

  //Bind and draw vertex buffers
  for(int i=0; i<list_data.size(); i++){
    Object* object = *next(list_data.begin(),i);

    if(object->draw_type_name == "point"){
      vk_camera->compute_mvp(object);
      vkCmdPushConstants(command_buffer, pipeline_layout, VK_SHADER_STAGE_VERTEX_BIT, 0, sizeof(glm::mat4), &object->mvp);
      VkBuffer vertexBuffers[] = {object->vbo_xyz, object->vbo_rgb};
      VkDeviceSize offsets[] = {0, 0};
      vkCmdBindVertexBuffers(command_buffer, 0, 2, vertexBuffers, offsets);
      vkCmdDraw(command_buffer, object->xyz.size(), 1, 0, 0);
    }
  }

  //---------------------------
}
void VK_command::command_drawing_line(VkCommandBuffer command_buffer, uint32_t current_frame){
  VK_data* vk_data = engineManager->get_vk_data();
  //---------------------------

  vector<Frame*> vec_frame = vk_image->get_vec_frame();
  Frame* frame = vec_frame[current_frame];

  //Bind pipeline
  VkPipeline pipeline = vk_pipeline->get_pipeline_line();
  VkPipelineLayout pipeline_layout = vk_pipeline->get_pipeline_layout_line();
  vkCmdBindPipeline(command_buffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline);

  //Bind descriptor
  list<Object*> list_data = vk_data->get_list_data();
  if(list_data.size() != 0){
    vkCmdBindDescriptorSets(command_buffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline_layout, 0, 1, &frame->descriptor_set, 0, nullptr);
  }

  //Bind and draw vertex buffers
  for(int i=0; i<list_data.size(); i++){
    Object* object = *next(list_data.begin(),i);

    if(object->draw_type_name == "line"){
      vk_camera->compute_mvp(object);
      vkCmdPushConstants(command_buffer, pipeline_layout, VK_SHADER_STAGE_VERTEX_BIT, 0, sizeof(glm::mat4), &object->mvp);
      VkBuffer vertexBuffers[] = {object->vbo_xyz, object->vbo_rgb};
      VkDeviceSize offsets[] = {0, 0};
      vkCmdSetLineWidth(command_buffer, object->draw_line_width);
      vkCmdBindVertexBuffers(command_buffer, 0, 2, vertexBuffers, offsets);
      vkCmdDraw(command_buffer, object->xyz.size(), 1, 0, 0);
    }
  }

  //---------------------------
}

//One time command
VkCommandBuffer VK_command::command_buffer_begin(){
  VK_command* vk_command = engineManager->get_vk_command();
  VkCommandPool commandPool = vk_command->get_command_pool();
  VkDevice device = vk_device->get_device();
  //---------------------------

  VkCommandBufferAllocateInfo allocInfo{};
  allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
  allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
  allocInfo.commandPool = commandPool;
  allocInfo.commandBufferCount = 1;

  VkCommandBuffer command_buffer;
  vkAllocateCommandBuffers(device, &allocInfo, &command_buffer);

  VkCommandBufferBeginInfo beginInfo{};
  beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
  beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

  vkBeginCommandBuffer(command_buffer, &beginInfo);

  //---------------------------
  return command_buffer;
}
void VK_command::command_buffer_end(VkCommandBuffer command_buffer){
  VK_command* vk_command = engineManager->get_vk_command();
  VkCommandPool commandPool = vk_command->get_command_pool();
  VkDevice device = vk_device->get_device();
  VkQueue queue_graphics = vk_device->get_queue_graphics();
  //---------------------------

  vkEndCommandBuffer(command_buffer);

  VkSubmitInfo submitInfo{};
  submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
  submitInfo.commandBufferCount = 1;
  submitInfo.pCommandBuffers = &command_buffer;

  vkQueueSubmit(queue_graphics, 1, &submitInfo, VK_NULL_HANDLE);
  vkQueueWaitIdle(queue_graphics);

  vkFreeCommandBuffers(device, commandPool, 1, &command_buffer);

  //---------------------------
}
