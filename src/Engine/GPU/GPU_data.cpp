#include "GPU_data.h"

#include "../Node_engine.h"
#include "../Vulkan/Engine.h"
#include "../Vulkan/Data/VK_buffer.h"
#include "../Vulkan/Data/VK_texture.h"
#include "../Vulkan/Data/VK_descriptor.h"
#include "../Vulkan/Data/VK_data.h"
#include "../Vulkan/Command/VK_command.h"


//Constructor / Destructor
GPU_data::GPU_data(Node_engine* node_engine){
  //---------------------------

  Engine* engineManager = node_engine->get_engineManager();
  this->vk_buffer = engineManager->get_vk_buffer();
  this->vk_texture = engineManager->get_vk_texture();
  this->vk_descriptor = engineManager->get_vk_descriptor();
  this->vk_command = engineManager->get_vk_command();
  this->vk_data = engineManager->get_vk_data();

  //---------------------------
}
GPU_data::~GPU_data(){}

//Insert function
void GPU_data::insert_object_for_drawing(Object* object){
  //---------------------------

  bool is_in_list = false;
  for(int i=0; i<list_draw.size(); i++){
    Object* object_list = *next(list_draw.begin(),i);
    if(object->ID == object_list->ID){
      is_in_list = true;
    }
  }

  if(is_in_list == false){
    list_draw.push_back(object);
    vk_data->set_list_data(list_draw);
  }

  //---------------------------
}
void GPU_data::insert_object_in_engine(Object* object){
  //---------------------------
  
  vk_buffer->create_buffer_xyz(object, object->xyz);

  if(object->rgb.size() != 0){
    vk_buffer->create_buffer_rgb(object, object->rgb);
  }

  if(object->uv.size() != 0){
    vk_buffer->create_buffer_uv(object, object->uv);
  }

  if(object->path_text != ""){
    vk_texture->load_texture(object);
  }
  vk_descriptor->update_descriptor_set(object);
  this->insert_object_for_drawing(object);

  //---------------------------
}

//Remove function
void GPU_data::remove_object_for_drawing(Object* object){
  //---------------------------

  bool is_in_list = false;
  for(int i=0; i<list_draw.size(); i++){
    Object* object_list = *next(list_draw.begin(),i);
    if(object->ID == object_list->ID){
      list_draw.remove(object_list);
      vk_data->set_list_data(list_draw);
    }
  }

  //---------------------------
}
