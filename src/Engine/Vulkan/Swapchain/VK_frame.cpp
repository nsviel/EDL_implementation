#include "VK_frame.h"
#include "VK_swapchain.h"

#include "../VK_engine.h"
#include "../Param_vulkan.h"
#include "../Command/VK_command.h"
#include "../Command/VK_synchronization.h"
#include "../Rendering/VK_framebuffer.h"
#include "../Attachment/VK_depth.h"
#include "../Attachment/VK_color.h"
#include "../Data/VK_texture.h"
#include "../Device/VK_physical_device.h"


//Constructor / Destructor
VK_frame::VK_frame(VK_engine* vk_engine){
  //---------------------------

  this->vk_engine = vk_engine;
  this->param_vulkan = vk_engine->get_param_vulkan();
  this->vk_physical_device = vk_engine->get_vk_physical_device();
  this->vk_texture = vk_engine->get_vk_texture();
  this->vk_synchronization = vk_engine->get_vk_synchronization();
  this->vk_color = vk_engine->get_vk_color();
  this->vk_swapchain = vk_engine->get_vk_swapchain();
  this->vk_framebuffer = vk_engine->get_vk_framebuffer();

  //---------------------------
}
VK_frame::~VK_frame(){}

//Main function
void VK_frame::init_image(){
  //---------------------------

  this->create_frame_swapchain();
  this->create_frame_inflight();

  //---------------------------
}
void VK_frame::cleanup(){
  //---------------------------

  this->clean_frame_swapchain();
  this->clean_frame_inflight();

  //---------------------------
}

//Creation function
void VK_frame::create_frame_swapchain(){
  VK_depth* vk_depth = vk_engine->get_vk_depth();
  //---------------------------

  //Swapchain images
  vector<Frame_swapchain*> vec_frame_swapchain;
  for(int i=0; i<param_vulkan->swapchain.vec_swapchain_image.size(); i++){
    Frame_swapchain* image = new Frame_swapchain();
    image->color.image = param_vulkan->swapchain.vec_swapchain_image[i];
    image->color.format = vk_color->find_color_format();
    image->color.view = vk_texture->create_image_view(image->color.image, image->color.format, VK_IMAGE_ASPECT_COLOR_BIT);
    vk_depth->create_depth_attachment(image);
    vk_framebuffer->create_framebuffer(image);
    vec_frame_swapchain.push_back(image);
  }

  //---------------------------
  param_vulkan->swapchain.vec_frame_swapchain = vec_frame_swapchain;
}
void VK_frame::create_frame_inflight(){
  VK_command* vk_command = vk_engine->get_vk_command();
  //---------------------------

  //Draw frames
  vector<Frame_inflight*> vec_frame_inflight;
  for(int i=0; i<param_vulkan->instance.max_frame; i++){
    Frame_inflight* frame = new Frame_inflight();
    vk_synchronization->create_sync_objects(frame);
    vec_frame_inflight.push_back(frame);
  }

  vk_command->create_command_buffer(vec_frame_inflight);

  //---------------------------
  param_vulkan->swapchain.vec_frame_inflight = vec_frame_inflight;
}

//Deletio function
void VK_frame::clean_frame_swapchain(){
  VK_depth* vk_depth = vk_engine->get_vk_depth();
  VK_framebuffer* vk_framebuffer = vk_engine->get_vk_framebuffer();
  //---------------------------

  //Vec images
  for(int i=0; i<param_vulkan->swapchain.vec_frame_swapchain.size(); i++){
    Frame_swapchain* image = param_vulkan->swapchain.vec_frame_swapchain[i];
    vkDestroyImageView(param_vulkan->device.device, image->color.view, nullptr);
    vk_depth->clean_depth_attachment(image);
    vk_framebuffer->clean_framebuffer(image);
    delete image;
  }
  param_vulkan->swapchain.vec_frame_swapchain.clear();

  //---------------------------
}
void VK_frame::clean_frame_inflight(){
  //---------------------------

  for(int i=0; i<param_vulkan->swapchain.vec_frame_inflight.size(); i++){
    Frame_inflight* frame = param_vulkan->swapchain.vec_frame_inflight[i];
    vk_synchronization->clean_sync_obj(frame);
    delete frame;
  }
  param_vulkan->swapchain.vec_frame_inflight.clear();

  //---------------------------
}
