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

  for(int i=0; i<list_data.size(); i++){
    Object* object = *next(list_data.begin(),i);
    this->clean_object(object);
  }

  //---------------------------
}
void VK_data::clean_object(Object* object){
  //---------------------------

  vkDeviceWaitIdle(param_vulkan->device);

  vk_buffer->cleanup_object(object);
  vk_texture->cleanup_texture(object);

  //---------------------------
}

//Data description
void VK_data::create_pipeline_data(Struct_pipeline* pipeline){
  //---------------------------

  this->create_vertex_description(pipeline);
  this->create_data_description(pipeline);
  this->combine_description(pipeline);

  //---------------------------
}

void VK_data::create_vertex_description(Struct_pipeline* pipeline){
  vector<VkVertexInputAttributeDescription> attribut_description;
  //---------------------------

  VkVertexInputAttributeDescription attribut_1{};
  attribut_1.binding = 0;
  attribut_1.location = 0;
  attribut_1.format = VK_FORMAT_R32G32B32_SFLOAT;
  attribut_1.offset = 0;
  attribut_description.push_back(attribut_1);

  VkVertexInputAttributeDescription attribut_2{};
  attribut_2.binding = 1;
  attribut_2.location = 1;
  attribut_2.format = VK_FORMAT_R32G32B32A32_SFLOAT;
  attribut_2.offset = 0;
  attribut_description.push_back(attribut_2);

  /*
  VkVertexInputAttributeDescription attribut_3{};
  attribut_3.binding = 2;
  attribut_3.location = 2;
  attribut_3.format = VK_FORMAT_R32G32_SFLOAT;
  attribut_3.offset = 0;
  attribut_description.push_back(attribut_3);
  */

  //---------------------------
  pipeline->attribut_description = attribut_description;
}
void VK_data::create_data_description(Struct_pipeline* pipeline){
  vector<VkVertexInputBindingDescription> data_description;
  //---------------------------

  // position buffer binding
  VkVertexInputBindingDescription desc_xyz{};
  desc_xyz.binding = 0;
  desc_xyz.stride = sizeof(glm::vec3);
  desc_xyz.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
  data_description.push_back(desc_xyz);

  // normal buffer binding
  VkVertexInputBindingDescription desc_rgb{};
  desc_rgb.binding = 1;
  desc_rgb.stride = sizeof(glm::vec4);
  desc_rgb.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
  data_description.push_back(desc_rgb);

  // texture coordinate buffer binding
  /*
  VkVertexInputBindingDescription desc_uv{};
  desc_uv.binding = 2;
  desc_uv.stride = sizeof(glm::vec2);
  desc_uv.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
  data_description.push_back(desc_uv);
  */

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
