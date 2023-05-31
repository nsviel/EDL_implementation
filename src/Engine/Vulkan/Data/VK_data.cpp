#include "VK_data.h"
#include "VK_buffer.h"
#include "VK_texture.h"

#include "../VK_engine.h"
#include "../VK_param.h"
#include "../Shader/Binding/VK_binding.h"

#include "../../GPU/GPU_data.h"
#include "../../Node_engine.h"


//Constructor / Destructor
VK_data::VK_data(VK_engine* vk_engine){
  //---------------------------

  this->vk_engine = vk_engine;
  this->vk_param = vk_engine->get_vk_param();
  this->vk_buffer = vk_engine->get_vk_buffer();
  this->vk_texture = vk_engine->get_vk_texture();
  this->vk_binding = vk_engine->get_vk_binding();

  //---------------------------
}
VK_data::~VK_data(){}

//Insertion function
void VK_data::insert_scene_object(Object* object){
  //---------------------------

  Struct_data* data = new Struct_data();
  data->object = object;
  data->binding.vec_required_binding.push_back(std::make_tuple("mvp", "mat4", 0, TYPE_UNIFORM, STAGE_VS));
  vk_binding->fill_binding_from_requirement(data->binding);
  this->check_for_attribut(data);
  vk_buffer->create_buffer(data);
  this->list_data_scene.push_back(data);

  //---------------------------
}
void VK_data::insert_glyph_object(Object* object){
  //---------------------------

  Struct_data* data = new Struct_data();
  data->object = object;
  data->binding.vec_required_binding.push_back(std::make_tuple("mvp", "mat4", 0, TYPE_UNIFORM, STAGE_VS));
  vk_binding->fill_binding_from_requirement(data->binding);
  this->check_for_attribut(data);
  vk_buffer->create_buffer(data);
  this->list_data_glyph.push_back(data);

  //---------------------------
}

//Clean function
void VK_data::cleanup(){
  //---------------------------

  //Data list Scene
  for(int i=0; i<list_data_scene.size(); i++){
    Struct_data* data = *next(list_data_scene.begin(),i);
    this->clean_data(data);
  }

  //Data list Glyph
  for(int i=0; i<list_data_glyph.size(); i++){
    Struct_data* data = *next(list_data_glyph.begin(),i);
    this->clean_data(data);
  }

  //---------------------------
}
void VK_data::clean_data(Struct_data* data){
  //---------------------------

  vkDeviceWaitIdle(vk_param->device.device);

  vk_buffer->clean_buffer(data);
  vk_texture->clean_texture(data);
  vk_binding->clean_binding(data->binding);

  //---------------------------
}
void VK_data::clean_data(int ID){
  //---------------------------

  for(int i=0; i<list_data_scene.size(); i++){
    Struct_data* data = *next(list_data_scene.begin(),i);
    if(data->object->ID == ID){
      this->clean_data(data);
      list_data_scene.remove(data);
    }
  }

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
void VK_data::check_for_attribut(Struct_data* data){
  //---------------------------

  if(data->object->rgb.size() != 0){
    data->has_rgb = true;
  }
  if(data->object->uv.size() != 0){
    data->has_uv = true;
  }

  //---------------------------
}
