#include "GPU_data.h"

#include "../Core_node.h"
#include "../Vulkan/VK_engine.h"
#include "../Vulkan/Data/VK_buffer.h"
#include "../Vulkan/Image/VK_texture.h"
#include "../Vulkan/Binding/VK_descriptor.h"
#include "../Vulkan/Data/VK_data.h"
#include "../Vulkan/Command/VK_command.h"


//Constructor / Destructor
GPU_data::GPU_data(Core_node* core_node){
  //---------------------------

  VK_engine* vk_engine = core_node->get_vk_engine();
  this->vk_buffer = vk_engine->get_vk_buffer();
  this->vk_texture = vk_engine->get_vk_texture();
  this->vk_descriptor = vk_engine->get_vk_descriptor();
  this->vk_command = vk_engine->get_vk_command();
  this->vk_data = vk_engine->get_vk_data();

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
      vk_data->clean_data_scene(object->ID);
    }
  }

  //---------------------------
}
