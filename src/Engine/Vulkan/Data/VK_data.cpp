#include "VK_data.h"
#include "VK_buffer.h"
#include "VK_texture.h"

#include "../Engine.h"
#include "../Param_vulkan.h"
#include "../Device/VK_device.h"

#include "../../GPU/GPU_data.h"
#include "../../Node_engine.h"


//Constructor / Destructor
VK_data::VK_data(Engine* engineManager){
  //---------------------------

  this->engineManager = engineManager;
  this->param_vulkan = engineManager->get_param_vulkan();
  this->vk_device = engineManager->get_vk_device();
  this->vk_buffer = engineManager->get_vk_buffer();
  this->vk_texture = engineManager->get_vk_texture();

  //---------------------------
}
VK_data::~VK_data(){}

//Main function
void VK_data::cleanup(){
  //---------------------------

  for(int i=0; i<list_obj_scene.size(); i++){
    Object* object = *next(list_obj_scene.begin(),i);
    this->clean_object(object);
  }

  for(int i=0; i<list_obj_glyph.size(); i++){
    Object* object = *next(list_obj_glyph.begin(),i);
    this->clean_object(object);
  }

  //---------------------------
}
void VK_data::clean_object(Object* object){
  //---------------------------

  vkDeviceWaitIdle(param_vulkan->device.device);

  vk_buffer->cleanup_object(object);
  vk_texture->cleanup_texture(object);

  //---------------------------
}

//Data description
void VK_data::create_data_description(Struct_pipeline* pipeline){
  //---------------------------

  this->create_vertex_description(pipeline);
  this->create_attribut_description(pipeline);
  this->combine_description(pipeline);

  //---------------------------
}

void VK_data::create_attribut_description(Struct_pipeline* pipeline){
  vector<VkVertexInputAttributeDescription> attribut_description;
  //---------------------------

  vector<string>& vec_data_name = pipeline->vec_data_name;
  for(int i=0; i<vec_data_name.size(); i++){
    VkVertexInputAttributeDescription attribut{};

    if(vec_data_name[i] == "location"){
      attribut.binding = 0;
      attribut.location = 0;
      attribut.format = VK_FORMAT_R32G32B32_SFLOAT;
      attribut.offset = 0;
    }
    else if(vec_data_name[i] == "color"){
      attribut.binding = 1;
      attribut.location = 1;
      attribut.format = VK_FORMAT_R32G32B32A32_SFLOAT;
      attribut.offset = 0;
    }
    else if(vec_data_name[i] == "tex_coord"){
      attribut.binding = 2;
      attribut.location = 2;
      attribut.format = VK_FORMAT_R32G32_SFLOAT;
      attribut.offset = 0;
    }
    else{
      cout<<"[error] data description"<<endl;
      break;
    }

    attribut_description.push_back(attribut);
  }

  //---------------------------
  pipeline->attribut_description = attribut_description;
}
void VK_data::create_vertex_description(Struct_pipeline* pipeline){
  vector<VkVertexInputBindingDescription> data_description;
  //---------------------------

  vector<string>& vec_data_name = pipeline->vec_data_name;
  for(int i=0; i<vec_data_name.size(); i++){
    VkVertexInputBindingDescription description{};

    if(vec_data_name[i] == "location"){
      description.binding = 0;
      description.stride = sizeof(glm::vec3);
      description.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
    }
    else if(vec_data_name[i] == "color"){
      description.binding = 1;
      description.stride = sizeof(glm::vec4);
      description.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
    }
    else if(vec_data_name[i] == "tex_coord"){
      description.binding = 2;
      description.stride = sizeof(glm::vec2);
      description.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
    }
    else{
      cout<<"[error] data description"<<endl;
      break;
    }

    data_description.push_back(description);
  }

  //---------------------------
  pipeline->data_description = data_description;
}
void VK_data::combine_description(Struct_pipeline* pipeline){
  //---------------------------

  VkPipelineVertexInputStateCreateInfo vertex_input_info{};
  vertex_input_info.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
  vertex_input_info.vertexBindingDescriptionCount = static_cast<uint32_t>(pipeline->data_description.size());
  vertex_input_info.vertexAttributeDescriptionCount = static_cast<uint32_t>(pipeline->attribut_description.size());
  vertex_input_info.pVertexBindingDescriptions = pipeline->data_description.data();
  vertex_input_info.pVertexAttributeDescriptions = pipeline->attribut_description.data();

  //---------------------------
  pipeline->vertex_input_info = vertex_input_info;
}
