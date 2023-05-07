#include "GPU_data.h"

#include "../Node_engine.h"
#include "../Vulkan/Engine.h"
#include "../Vulkan/Data/VK_buffer.h"
#include "../Vulkan/Data/VK_texture.h"
#include "../Vulkan/Data/VK_descriptor.h"


//Constructor / Destructor
GPU_data::GPU_data(Node_engine* node_engine){
  //---------------------------

  Engine* engineManager = node_engine->get_engineManager();
  this->vk_buffer = engineManager->get_vk_buffer();
  this->vk_texture = engineManager->get_vk_texture();
  this->vk_descriptor = engineManager->get_vk_descriptor();

  //---------------------------
}
GPU_data::~GPU_data(){}

//Main function
void GPU_data::draw_object(Object* object){
  //---------------------------


  //---------------------------
}
void GPU_data::insert_object_in_engine(Object* object){
  //---------------------------

  vk_texture->load_texture(object->path_texture);
  vk_buffer->create_buffer_xyz(object, object->xyz);
  vk_buffer->create_buffer_rgb(object, object->rgb);
  vk_buffer->create_buffer_uv(object, object->uv);
  vk_descriptor->create_descriptor_set();

  //---------------------------
}
