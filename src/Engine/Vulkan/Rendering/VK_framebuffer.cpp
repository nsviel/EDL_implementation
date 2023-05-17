#include "VK_framebuffer.h"
#include "VK_depth.h"

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
  VkDevice device = vk_device->get_device();
  //---------------------------

  //Get FBO required elements
  VkExtent2D swapchain_extent = vk_swapchain->get_extent();
  VkRenderPass renderPass = vk_renderpass->get_renderPass();
  VkFramebuffer fbo;

  //Create frambuffer
  std::array<VkImageView, 2> attachments = {image->image_view, image->depth_view};

  VkFramebufferCreateInfo framebufferInfo{};
  framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
  framebufferInfo.renderPass = renderPass;
  framebufferInfo.attachmentCount = static_cast<uint32_t>(attachments.size());
  framebufferInfo.pAttachments = attachments.data();
  framebufferInfo.width = swapchain_extent.width;
  framebufferInfo.height = swapchain_extent.height;
  framebufferInfo.layers = 1;

  VkResult result = vkCreateFramebuffer(device, &framebufferInfo, nullptr, &fbo);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to create framebuffer!");
  }

  //---------------------------
  image->fbo_vec.push_back(fbo);
}

//Deletion function
void VK_framebuffer::clean_framebuffer(Image* image){
  VkDevice device = vk_device->get_device();
  //---------------------------

  for(int j=0; j<image->fbo_vec.size(); j++){
    vkDestroyFramebuffer(device, image->fbo_vec[j], nullptr);
  }

  //---------------------------
}
