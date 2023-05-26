#include "VK_image.h"
#include "VK_swapchain.h"

#include "../Engine.h"
#include "../Param_vulkan.h"
#include "../Command/VK_command.h"
#include "../Command/VK_synchronization.h"
#include "../Rendering/VK_framebuffer.h"
#include "../Attachment/VK_depth.h"
#include "../Attachment/VK_color.h"
#include "../Data/VK_texture.h"
#include "../Device/VK_physical_device.h"


//Constructor / Destructor
VK_image::VK_image(Engine* engineManager){
  //---------------------------

  this->engineManager = engineManager;
  this->param_vulkan = engineManager->get_param_vulkan();
  this->vk_physical_device = engineManager->get_vk_physical_device();
  this->vk_texture = engineManager->get_vk_texture();
  this->vk_synchronization = engineManager->get_vk_synchronization();
  this->vk_color = engineManager->get_vk_color();
  this->vk_swapchain = engineManager->get_vk_swapchain();
  this->vk_framebuffer = engineManager->get_vk_framebuffer();

  //---------------------------
}
VK_image::~VK_image(){}

//Main function
void VK_image::init_image(){
  //---------------------------

  this->create_image_struct();
  this->create_frame_struct();

  //---------------------------
}
void VK_image::cleanup(){
  //---------------------------

  this->clean_image_struct();
  this->clean_frame_struct();

  //---------------------------
}

//Creation function
void VK_image::create_image_struct(){
  VK_depth* vk_depth = engineManager->get_vk_depth();
  //---------------------------

  //Swapchain images
  vector<Image*> vec_image;
  for(int i=0; i<param_vulkan->swapchain.vec_swapchain_image.size(); i++){
    Image* image = new Image();
    image->color.image = param_vulkan->swapchain.vec_swapchain_image[i];
    image->color.format = vk_color->find_color_format();
    image->color.view = vk_texture->create_image_view(image->color.image, image->color.format, VK_IMAGE_ASPECT_COLOR_BIT);
    vk_depth->create_depth_attachment(image);
    vk_framebuffer->create_framebuffer(image);
    vec_image.push_back(image);
  }

  //---------------------------
  param_vulkan->swapchain.vec_image = vec_image;
}
void VK_image::create_frame_struct(){
  VK_command* vk_command = engineManager->get_vk_command();
  //---------------------------

  //Draw frames
  vector<Frame*> vec_frame;
  for(int i=0; i<param_vulkan->instance.max_frame; i++){
    Frame* frame = new Frame();
    vk_synchronization->create_sync_objects(frame);
    vec_frame.push_back(frame);
  }

  vk_command->create_command_buffer(vec_frame);

  //---------------------------
  param_vulkan->swapchain.vec_frame = vec_frame;
}

//Deletio function
void VK_image::clean_image_struct(){
  VK_depth* vk_depth = engineManager->get_vk_depth();
  VK_framebuffer* vk_framebuffer = engineManager->get_vk_framebuffer();
  //---------------------------

  //Vec images
  for(int i=0; i<param_vulkan->swapchain.vec_image.size(); i++){
    Image* image = param_vulkan->swapchain.vec_image[i];
    vkDestroyImageView(param_vulkan->device.device, image->color.view, nullptr);
    vk_depth->clean_depth_attachment(image);
    vk_framebuffer->clean_framebuffer(image);
    delete image;
  }
  param_vulkan->swapchain.vec_image.clear();

  //---------------------------
}
void VK_image::clean_frame_struct(){
  //---------------------------

  for(int i=0; i<param_vulkan->swapchain.vec_frame.size(); i++){
    Frame* frame = param_vulkan->swapchain.vec_frame[i];
    vk_synchronization->clean_sync_obj(frame);
    delete frame;
  }
  param_vulkan->swapchain.vec_frame.clear();

  //---------------------------
}
