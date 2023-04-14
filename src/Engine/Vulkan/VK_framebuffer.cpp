#include "VK_framebuffer.h"
#include "Engine_vulkan.h"

#include "../Node_engine.h"



//Constructor / Destructor
VK_framebuffer::VK_framebuffer(Engine_vulkan* engine_vulkan){
  //---------------------------

  this->engine_vulkan = engine_vulkan;

  //---------------------------
}
VK_framebuffer::~VK_framebuffer(){}

//Main function
void VK_framebuffer::create_framebuffers(){
  std::vector<VkImageView> swapChain_image_views = engine_vulkan->get_swapChain_image_views();
  VkExtent2D swapChain_extent = engine_vulkan->get_swapChain_extent();
  VkDevice device = engine_vulkan->get_device();
  VkRenderPass renderPass = engine_vulkan->get_renderPass();
  //---------------------------

  //Resize to hold all fbos
  swapChain_fbo.resize(swapChain_image_views.size());

  //Create frambuffer
  for(size_t i=0; i<swapChain_image_views.size(); i++){
    VkImageView attachments[] = {
      swapChain_image_views[i]
    };

    VkFramebufferCreateInfo framebufferInfo{};
    framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    framebufferInfo.renderPass = renderPass;
    framebufferInfo.attachmentCount = 1;
    framebufferInfo.pAttachments = attachments;
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
