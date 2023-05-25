#include "VK_framebuffer.h"

#include "../Attachment/VK_depth.h"
#include "../Engine.h"
#include "../Param_vulkan.h"
#include "../Swapchain/VK_swapchain.h"
#include "../Swapchain/VK_image.h"
#include "../Pipeline/VK_renderpass.h"
#include "../Device/VK_device.h"


//Constructor / Destructor
VK_framebuffer::VK_framebuffer(Engine* engineManager){
  //---------------------------

  this->param_vulkan = engineManager->get_param_vulkan();
  this->vk_device = engineManager->get_vk_device();
  this->vk_swapchain = engineManager->get_vk_swapchain();
  this->vk_renderpass = engineManager->get_vk_renderpass();
  this->vk_depth = engineManager->get_vk_depth();
  this->vk_image = engineManager->get_vk_image();

  //---------------------------
}
VK_framebuffer::~VK_framebuffer(){}

//FBO creation
void VK_framebuffer::create_framebuffer_obj(){
  vector<Image*> vec_image_obj = vk_image->get_vec_image();
  //---------------------------

  //Create frambuffer
  for(size_t i=0; i<vec_image_obj.size(); i++){
    Image* image = vec_image_obj[i];
    this->create_framebuffer(image);
  }

  //---------------------------
}
void VK_framebuffer::create_framebuffer(Image* image){
  //---------------------------

  //Get FBO required elements
  VkRenderPass renderPass = vk_renderpass->get_renderPass();
  VkFramebuffer fbo;

  //Create frambuffer
  std::array<VkImageView, 2> attachments = {image->color.view, image->depth.view};

  VkFramebufferCreateInfo framebufferInfo{};
  framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
  framebufferInfo.renderPass = renderPass;
  framebufferInfo.attachmentCount = static_cast<uint32_t>(attachments.size());
  framebufferInfo.pAttachments = attachments.data();
  framebufferInfo.width = param_vulkan->extent.width;
  framebufferInfo.height = param_vulkan->extent.height;
  framebufferInfo.layers = 1;

  VkResult result = vkCreateFramebuffer(param_vulkan->device, &framebufferInfo, nullptr, &fbo);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to create framebuffer!");
  }

  //---------------------------
  image->fbo = fbo;
}

//Deletion function
void VK_framebuffer::clean_framebuffer(Image* image){
  //---------------------------

  vkDestroyFramebuffer(param_vulkan->device, image->fbo, nullptr);

  //---------------------------
}
