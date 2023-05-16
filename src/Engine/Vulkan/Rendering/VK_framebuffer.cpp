#include "VK_framebuffer.h"
#include "VK_depth.h"

#include "../Swapchain/VK_swapchain.h"
#include "../Swapchain/VK_image.h"
#include "../Pipeline/VK_renderpass.h"
#include "../Device/VK_device.h"
#include "../Engine.h"

#include "../../Node_engine.h"



//Constructor / Destructor
VK_framebuffer::VK_framebuffer(Engine* engineManager){
  //---------------------------

  this->engineManager = engineManager;
  this->vk_device = engineManager->get_vk_device();
  this->vk_swapchain = engineManager->get_vk_swapchain();
  this->vk_renderpass = engineManager->get_vk_renderpass();
  this->vk_depth = engineManager->get_vk_depth();
  this->vk_image = engineManager->get_vk_image();

  //---------------------------
}
VK_framebuffer::~VK_framebuffer(){}

//Main function
void VK_framebuffer::init_fbo(){
  //---------------------------

  this->create_framebuffers();

  //---------------------------
}
void VK_framebuffer::cleanup(){
  VkDevice device = vk_device->get_device();
  //---------------------------

  for(auto framebuffer : fbo_vec){
    vkDestroyFramebuffer(device, framebuffer, nullptr);
  }

  //---------------------------
}

//FBO creation
void VK_framebuffer::create_framebuffers(){
  //---------------------------

  //Get FBO required elements
  std::vector<VkImageView> swapChain_image_views = vk_image->get_swapChain_image_views();
  VkExtent2D swapchain_extent = vk_swapchain->get_extent();
  VkDevice device = vk_device->get_device();
  VkRenderPass renderPass = vk_renderpass->get_renderPass();
  VkImageView depth_image_view = vk_depth->get_depthImageView();

  //Resize to hold all fbos
  this->fbo_vec.resize(swapChain_image_views.size());

  //Create frambuffer
  for(size_t i=0; i<swapChain_image_views.size(); i++){
    std::array<VkImageView, 2> attachments = {swapChain_image_views[i], depth_image_view};

    VkFramebufferCreateInfo framebufferInfo{};
    framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    framebufferInfo.renderPass = renderPass;
    framebufferInfo.attachmentCount = static_cast<uint32_t>(attachments.size());
    framebufferInfo.pAttachments = attachments.data();
    framebufferInfo.width = swapchain_extent.width;
    framebufferInfo.height = swapchain_extent.height;
    framebufferInfo.layers = 1;

    VkResult result = vkCreateFramebuffer(device, &framebufferInfo, nullptr, &fbo_vec[i]);
    if(result != VK_SUCCESS){
      throw std::runtime_error("[error] failed to create framebuffer!");
    }
  }

  //---------------------------
}
