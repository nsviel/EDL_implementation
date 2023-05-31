#include "VK_data.h"
#include "VK_buffer.h"
#include "VK_texture.h"

#include "../Engine.h"
#include "../Param_vulkan.h"
#include "../Device/VK_device.h"
#include "../Shader/VK_descriptor.h"
#include "../Shader/VK_uniform.h"

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
  this->vk_descriptor = engineManager->get_vk_descriptor();
  this->vk_uniform = engineManager->get_vk_uniform();

  //---------------------------
}
VK_data::~VK_data(){}

//Insertion function
void VK_data::insert_scene_object(Object* object){
  //---------------------------

  Struct_data* data = new Struct_data();
  data->object = object;
  data->binding.vec_required_binding.push_back(std::make_tuple("mvp", "mat4", 0, TYPE_UNIFORM, STAGE_VS));
  data->binding.descriptor.layout = vk_descriptor->create_layout_from_required(data->binding.vec_required_binding);
  this->check_for_attribut(data);
  vk_buffer->create_buffer(data);
  this->list_data_scene.push_back(data);

  //vk_uniform->create_uniform_buffers(data->binding.vec_required_binding, data->binding.vec_uniform);
  //vk_descriptor->allocate_descriptor_set(data->binding.descriptor.layout, data->binding.descriptor.set);
  //vk_descriptor->update_descriptor_set(data->binding);

  //---------------------------
}
void VK_data::insert_glyph_object(Object* object){
  //---------------------------

  Struct_data* data = new Struct_data();
  data->object = object;
  data->binding.vec_required_binding.push_back(std::make_tuple("mvp", "mat4", 0, TYPE_UNIFORM, STAGE_VS));
  data->binding.descriptor.layout = vk_descriptor->create_layout_from_required(data->binding.vec_required_binding);
  this->check_for_attribut(data);
  vk_buffer->create_buffer(data);
  this->list_data_glyph.push_back(data);

  //---------------------------
}

//Clean function
void VK_data::cleanup(){
  //---------------------------

  for(int i=0; i<list_data_scene.size(); i++){
    Struct_data* data = *next(list_data_scene.begin(),i);
    this->clean_data(data);
  }

  for(int i=0; i<list_data_glyph.size(); i++){
    Struct_data* data = *next(list_data_glyph.begin(),i);
    this->clean_data(data);
  }

  //---------------------------
}
void VK_data::clean_data(Struct_data* data){
  //---------------------------

  vkDeviceWaitIdle(param_vulkan->device.device);
  vkDestroyDescriptorSetLayout(param_vulkan->device.device, data->binding.descriptor.layout, nullptr);

  vk_buffer->clean_data(data);
  vk_texture->clean_texture(data->object);
  //vk_uniform->clean_uniform(data->binding);

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
