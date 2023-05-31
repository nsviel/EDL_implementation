#include "VK_frame.h"
#include "VK_swapchain.h"

#include "../../VK_engine.h"
#include "../../VK_param.h"
#include "../../Pipeline/Command/VK_command.h"
#include "../../Pipeline/Command/VK_synchronization.h"
#include "../../Pipeline/Renderpass/VK_framebuffer.h"
#include "../../Pipeline/Attachment/VK_depth.h"
#include "../../Pipeline/Attachment/VK_color.h"
#include "../../Data/VK_texture.h"
#include "../../Instance/Device/VK_physical_device.h"


//Constructor / Destructor
VK_frame::VK_frame(VK_engine* vk_engine){
  //---------------------------

  this->vk_engine = vk_engine;
  this->vk_param = vk_engine->get_vk_param();
  this->vk_physical_device = vk_engine->get_vk_physical_device();
  this->vk_texture = vk_engine->get_vk_texture();
  this->vk_synchronization = vk_engine->get_vk_synchronization();
  this->vk_color = vk_engine->get_vk_color();
  this->vk_swapchain = vk_engine->get_vk_swapchain();
  this->vk_framebuffer = vk_engine->get_vk_framebuffer();
  this->vk_depth = vk_engine->get_vk_depth();

  //---------------------------
}
VK_frame::~VK_frame(){}

//Main function
void VK_frame::init_image(){
  //---------------------------

  this->create_frame_swapchain(vk_param->renderpass_scene.vec_frame_swapchain);
  this->create_frame_inflight();

  //---------------------------
}
void VK_frame::cleanup(){
  //---------------------------

  this->clean_frame_swapchain(vk_param->renderpass_scene.vec_frame_swapchain);
  this->clean_frame_inflight();

  //---------------------------
}

//Creation function
void VK_frame::create_frame_swapchain(vector<Frame_swapchain*>& vec_frame){
  //---------------------------

  //Swapchain images
  for(int i=0; i<vk_param->swapchain.vec_swapchain_image.size(); i++){
    Frame_swapchain* image = new Frame_swapchain();
    image->color.image = vk_param->swapchain.vec_swapchain_image[i];
    image->color.format = vk_color->find_color_format();
    image->color.view = vk_texture->create_image_view(image->color.image, image->color.format, VK_IMAGE_ASPECT_COLOR_BIT);
    vk_depth->create_depth_attachment(image);
    vk_framebuffer->create_framebuffer(image);
    vec_frame.push_back(image);
  }

  //---------------------------
}
void VK_frame::create_frame_inflight(){
  VK_command* vk_command = vk_engine->get_vk_command();
  //---------------------------

  //Draw frames
  vector<Frame_inflight*> vec_frame_inflight;
  for(int i=0; i<vk_param->instance.max_frame; i++){
    Frame_inflight* frame = new Frame_inflight();
    vk_synchronization->create_sync_objects(frame);
    vec_frame_inflight.push_back(frame);
  }

  vk_command->create_command_buffer(vec_frame_inflight);

  //---------------------------
  vk_param->swapchain.vec_frame_inflight = vec_frame_inflight;
}

//Deletio function
void VK_frame::clean_frame_swapchain(vector<Frame_swapchain*>& vec_frame){
  //---------------------------

  //Vec images
  for(int i=0; i<vec_frame.size(); i++){
    Frame_swapchain* image = vec_frame[i];
    vkDestroyImageView(vk_param->device.device, image->color.view, nullptr);
    vk_depth->clean_depth_attachment(image);
    vk_framebuffer->clean_framebuffer(image);
    delete image;
  }
  vec_frame.clear();

  //---------------------------
}
void VK_frame::clean_frame_inflight(){
  //---------------------------

  for(int i=0; i<vk_param->swapchain.vec_frame_inflight.size(); i++){
    Frame_inflight* frame = vk_param->swapchain.vec_frame_inflight[i];
    vk_synchronization->clean_sync_obj(frame);
    delete frame;
  }
  vk_param->swapchain.vec_frame_inflight.clear();

  //---------------------------
}
