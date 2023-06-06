#include "VK_frame.h"
#include "VK_swapchain.h"

#include "../../VK_engine.h"
#include "../../VK_param.h"
#include "../../Pipeline/Command/VK_command.h"
#include "../../Pipeline/Command/VK_synchronization.h"
#include "../../Pipeline/Renderpass/VK_framebuffer.h"
#include "../../Pipeline/Attachment/VK_depth.h"
#include "../../Pipeline/Attachment/VK_color.h"
#include "../../Pipeline/Image/VK_texture.h"
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

//Renderpass frame
void VK_frame::create_frame_renderpass(Struct_renderpass* renderpass){
  VK_command* vk_command = vk_engine->get_vk_command();
  //---------------------------

  for(int i=0; i<vk_param->swapchain.vec_swapchain_image.size(); i++){
    Frame* frame = new Frame();
    frame->color.image = vk_param->swapchain.vec_swapchain_image[i];
    frame->color.format = vk_color->find_color_format();
    frame->color.view = vk_texture->create_image_view(frame->color.image, frame->color.format, VK_IMAGE_ASPECT_COLOR_BIT);

    vk_depth->create_depth_attachment(frame);
    vk_framebuffer->create_framebuffer(renderpass, frame);
    vk_synchronization->init_frame_sync(frame);

    renderpass->frame_set->vec_frame.push_back(frame);
  }

  //---------------------------
}
void VK_frame::clean_frame_renderpass(Struct_renderpass* renderpass){
  vector<Frame*>& vec_frame = renderpass->frame_set->vec_frame;
  //---------------------------

  //Vec images
  for(int i=0; i<vec_frame.size(); i++){
    Frame* frame = vec_frame[i];
    vkDestroyImageView(vk_param->device.device, frame->color.view, nullptr);
    vk_depth->clean_depth_attachment(frame);
    vk_framebuffer->clean_framebuffer(frame);
    vk_synchronization->clean_frame_sync(frame);
    delete frame;
  }
  vec_frame.clear();

  //---------------------------
}
