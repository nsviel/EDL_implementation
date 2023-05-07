#include "VK_data.h"

#include "../Engine.h"

#include "../../GPU/GPU_data.h"
#include "../../Node_engine.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "../../../../extern/tiny_obj_loader.h"


//Constructor / Destructor
VK_data::VK_data(Engine* engineManager){
  //---------------------------

  this->engineManager = engineManager;

  //---------------------------
}
VK_data::~VK_data(){}

//Main function
Mesh* VK_data::load_model(){
  Node_engine* node_engine = engineManager->get_node_engine();
  GPU_data* gpu_data = node_engine->get_gpu_data();
  //---------------------------

  Mesh* object = new Mesh();
  object->path_file = "../src/Engine/Texture/viking_room.obj";
  object->path_text = "../src/Engine/Texture/viking_room.png";
  object->draw_type_name = "point";

  tinyobj::attrib_t attrib;
  std::vector<tinyobj::shape_t> shapes;
  std::vector<tinyobj::material_t> materials;
  std::string warn, err;

  bool load_ok = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, object->path_file.c_str());
  if(!load_ok){
    throw std::runtime_error(warn + err);
  }

  for(const auto& shape : shapes){
    for(const auto& index : shape.mesh.indices){
      vec3 xyz{
        attrib.vertices[3 * index.vertex_index + 0],
        attrib.vertices[3 * index.vertex_index + 1],
        attrib.vertices[3 * index.vertex_index + 2]
      };
      vec2 uv{
        attrib.texcoords[2 * index.texcoord_index + 0],
        1.0f - attrib.texcoords[2 * index.texcoord_index + 1]
      };

      object->xyz.push_back(xyz);
      object->rgb.push_back(vec4(1, 1, 1, 1));
      object->uv.push_back(uv);
    }
  }

  gpu_data->insert_object_in_engine(object);

  //---------------------------
  return object;
}
std::vector<VkVertexInputAttributeDescription> VK_data::description_vertex(){
  std::vector<VkVertexInputAttributeDescription> attributeDescriptions;
  //---------------------------

  VkVertexInputAttributeDescription attribut_1{};
  attribut_1.binding = 0;
  attribut_1.location = 0;
  attribut_1.format = VK_FORMAT_R32G32B32_SFLOAT;
  attribut_1.offset = 0;
  attributeDescriptions.push_back(attribut_1);

  VkVertexInputAttributeDescription attribut_2{};
  attribut_2.binding = 1;
  attribut_2.location = 1;
  attribut_2.format = VK_FORMAT_R32G32B32A32_SFLOAT;
  attribut_2.offset = 0;
  attributeDescriptions.push_back(attribut_2);

  VkVertexInputAttributeDescription attribut_3{};
  attribut_3.binding = 2;
  attribut_3.location = 2;
  attribut_3.format = VK_FORMAT_R32G32_SFLOAT;
  attribut_3.offset = 0;
  attributeDescriptions.push_back(attribut_3);

  //---------------------------
  return attributeDescriptions;
}
std::vector<VkVertexInputBindingDescription> VK_data::description_binding(){
  std::vector<VkVertexInputBindingDescription> bindingDescriptions;
  //---------------------------

  // position buffer binding
  VkVertexInputBindingDescription desc_xyz{};
  desc_xyz.binding = 0;
  desc_xyz.stride = sizeof(glm::vec3);
  desc_xyz.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
  bindingDescriptions.push_back(desc_xyz);

  // normal buffer binding
  VkVertexInputBindingDescription desc_rgb{};
  desc_rgb.binding = 1;
  desc_rgb.stride = sizeof(glm::vec4);
  desc_rgb.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
  bindingDescriptions.push_back(desc_rgb);

  // texture coordinate buffer binding
  VkVertexInputBindingDescription desc_uv{};
  desc_uv.binding = 2;
  desc_uv.stride = sizeof(glm::vec2);
  desc_uv.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
  bindingDescriptions.push_back(desc_uv);

  //---------------------------
  return bindingDescriptions;
}
