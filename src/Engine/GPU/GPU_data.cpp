#include "GPU_data.h"

#include "../Node_engine.h"
#include "../Vulkan/Engine.h"
#include "../Vulkan/Data/VK_buffer.h"
#include "../Vulkan/Data/VK_texture.h"
#include "../Vulkan/Shader/VK_descriptor.h"
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

//Main function
void GPU_data::insert_object_in_engine(Object* object){
  //---------------------------

  //Check if object already in engine
  bool is_in_list = false;
  for(int i=0; i<list_scene.size(); i++){
    Object* object_list = *next(list_scene.begin(),i);
    if(object->ID == object_list->ID){
      is_in_list = true;
    }
  }

  //If not, insert it
  if(is_in_list == false){
    list_scene.push_back(object);
    vk_data->insert_scene_object(object);
  }

  //---------------------------
}
void GPU_data::insert_glyph_in_engine(Object* object){
  //---------------------------

  //Check if object already in engine
  bool is_in_list = false;
  for(int i=0; i<list_glyph.size(); i++){
    Object* object_list = *next(list_glyph.begin(),i);
    if(object->ID == object_list->ID){
      is_in_list = true;
    }
  }

  //If not, insert it
  if(is_in_list == false){
    list_glyph.push_back(object);
    vk_data->insert_glyph_object(object);
  }

  //---------------------------
}
void GPU_data::remove_object_in_engine(Object* object){
  //---------------------------

  bool is_in_list = false;
  for(int i=0; i<list_scene.size(); i++){
    Object* object_list = *next(list_scene.begin(),i);
    if(object->ID == object_list->ID){
      list_scene.remove(object_list);
      vk_data->clean_data(object->ID);
    }
  }

  //---------------------------
}
