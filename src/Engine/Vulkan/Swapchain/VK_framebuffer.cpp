#include "VK_framebuffer.h"
#include "VK_swapchain.h"
#include "VK_depth.h"

#include "../Pipeline/VK_renderpass.h"
#include "../Device/VK_device.h"
#include "../Engine_vulkan.h"

#include "../../Node_engine.h"



//Constructor / Destructor
VK_framebuffer::VK_framebuffer(Engine_vulkan* engine_vulkan){
  //---------------------------

  this->engine_vulkan = engine_vulkan;
  this->vk_device = engine_vulkan->get_vk_device();
  this->vk_swapchain = engine_vulkan->get_vk_swapchain();
  this->vk_renderpass = engine_vulkan->get_vk_renderpass();

  //---------------------------
}
VK_framebuffer::~VK_framebuffer(){}

//Main function
void VK_framebuffer::create_framebuffers(){
  std::vector<VkImageView> swapChain_image_views = vk_swapchain->get_swapChain_image_views();
  VkExtent2D swapChain_extent = vk_swapchain->get_swapChain_extent();
  VkDevice device = vk_device->get_device();
  VkRenderPass renderPass = vk_renderpass->get_renderPass();
  VK_depth* vk_depth = engine_vulkan->get_vk_depth();
  //---------------------------

  VkImageView depthImageView = vk_depth->get_depthImageView();


  //Resize to hold all fbos
  swapChain_fbo.resize(swapChain_image_views.size());

  //Create frambuffer
  for(size_t i=0; i<swapChain_image_views.size(); i++){
    std::array<VkImageView, 2> attachments = {
      swapChain_image_views[i],
      depthImageView
    };

    VkFramebufferCreateInfo framebufferInfo{};
    framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    framebufferInfo.renderPass = renderPass;
    framebufferInfo.attachmentCount = static_cast<uint32_t>(attachments.size());
    framebufferInfo.pAttachments = attachments.data();
    framebufferInfo.width = swapChain_extent.width;
    framebufferInfo.height = swapChain_extent.height;
    framebufferInfo.layers = 1;

    VkResult result = vkCreateFramebuffer(device, &framebufferInfo, nullptr, &swapChain_fbo[i]);
    if(result != VK_SUCCESS){
      throw std::runtime_error("[error] failed to create framebuffer!");
    }
  }

  //---------------------------
}
void VK_framebuffer::cleanup(){
  VkDevice device = vk_device->get_device();
  //---------------------------

  for(auto framebuffer : swapChain_fbo){
    vkDestroyFramebuffer(device, framebuffer, nullptr);
  }

  //---------------------------
}
