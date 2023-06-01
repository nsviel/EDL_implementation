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

  this->create_frame_renderpass(&vk_param->renderpass_scene);
  this->create_frame_renderpass(&vk_param->renderpass_canva);

  //---------------------------
}
void VK_frame::cleanup(){
  //---------------------------

  this->clean_frame_swapchain(&vk_param->renderpass_scene);
  this->clean_frame_swapchain(&vk_param->renderpass_canva);

  //---------------------------
}

//Renderpass frame
void VK_frame::create_frame_renderpass(Struct_renderpass* renderpass){
  VK_command* vk_command = vk_engine->get_vk_command();
  vector<Frame*>& vec_frame = renderpass->vec_frame;
  //---------------------------

  //Renderpass images
  for(int i=0; i<vk_param->swapchain.vec_swapchain_image.size(); i++){
    Frame* image = new Frame();
    image->color.image = vk_param->swapchain.vec_swapchain_image[i];
    image->color.format = vk_color->find_color_format();
    image->color.view = vk_texture->create_image_view(image->color.image, image->color.format, VK_IMAGE_ASPECT_COLOR_BIT);

    vk_depth->create_depth_attachment(image);
    vk_framebuffer->create_framebuffer(renderpass, image);
    vk_synchronization->create_sync_objects(image);
    
    vec_frame.push_back(image);
  }

  vk_command->allocate_command_buffer(vec_frame);

  //---------------------------
}
void VK_frame::clean_frame_swapchain(Struct_renderpass* renderpass){
  vector<Frame*>& vec_frame = renderpass->vec_frame;
  //---------------------------

  //Vec images
  for(int i=0; i<vec_frame.size(); i++){
    Frame* image = vec_frame[i];
    vkDestroyImageView(vk_param->device.device, image->color.view, nullptr);
    vk_depth->clean_depth_attachment(image);
    vk_framebuffer->clean_framebuffer(image);
    vk_synchronization->clean_sync_obj(image);
    delete image;
  }
  vec_frame.clear();

  //---------------------------
}
