#include "VK_framebuffer.h"
#include "VK_renderpass.h"

#include "../Attachment/VK_depth.h"

#include "../../VK_engine.h"
#include "../../VK_param.h"
#include "../../Presentation/Swapchain/VK_swapchain.h"
#include "../../Presentation/Swapchain/VK_frame.h"
#include "../../Instance/Device/VK_device.h"


//Constructor / Destructor
VK_framebuffer::VK_framebuffer(VK_engine* vk_engine){
  //---------------------------

  this->vk_param = vk_engine->get_vk_param();
  this->vk_renderpass = vk_engine->get_vk_renderpass();

  //---------------------------
}
VK_framebuffer::~VK_framebuffer(){}

//FBO creation
void VK_framebuffer::create_framebuffer(Frame_renderpass* image){
  //---------------------------

  //Get FBO required elements
  VkRenderPass renderPass = vk_param->renderpass_scene.renderpass;
  VkFramebuffer fbo;

  //Create frambuffer
  std::array<VkImageView, 2> attachments = {image->color.view, image->depth.view};

  VkFramebufferCreateInfo framebufferInfo{};
  framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
  framebufferInfo.renderPass = renderPass;
  framebufferInfo.attachmentCount = static_cast<uint32_t>(attachments.size());
  framebufferInfo.pAttachments = attachments.data();
  framebufferInfo.width = vk_param->window.extent.width;
  framebufferInfo.height = vk_param->window.extent.height;
  framebufferInfo.layers = 1;

  VkResult result = vkCreateFramebuffer(vk_param->device.device, &framebufferInfo, nullptr, &fbo);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to create framebuffer!");
  }

  //---------------------------
  image->fbo = fbo;
}

//Deletion function
void VK_framebuffer::clean_framebuffer(Frame_renderpass* image){
  //---------------------------

  vkDestroyFramebuffer(vk_param->device.device, image->fbo, nullptr);

  //---------------------------
}
