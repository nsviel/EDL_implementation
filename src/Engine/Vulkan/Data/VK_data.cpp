#include "VK_data.h"
#include "VK_buffer.h"

#include "../Engine_vulkan.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "../../../../extern/tiny_obj_loader.h"


//Constructor / Destructor
VK_data::VK_data(Engine_vulkan* engine_vulkan){
  //---------------------------

  this->engine_vulkan = engine_vulkan;
  this->vk_buffer = engine_vulkan->get_vk_buffer();

  //---------------------------
}
VK_data::~VK_data(){}

//Main function
Cloud* VK_data::load_model(){
  //---------------------------
  const std::string MODEL_PATH = "../src/Engine/Texture/viking_room.obj";
  const std::string TEXTURE_PATH = "../src/Engine/Texture/viking_room.png";

  Cloud* cloud = new Cloud();
  cloud->path_file = "../src/Engine/Texture/viking_room.obj";
  cloud->path_texture = "../src/Engine/Texture/viking_room.png";



  tinyobj::attrib_t attrib;
  std::vector<tinyobj::shape_t> shapes;
  std::vector<tinyobj::material_t> materials;
  std::string warn, err;

  bool load_ok = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, MODEL_PATH.c_str());
  if(!load_ok){
    throw std::runtime_error(warn + err);
  }

  std::vector<Vertex> vertices;
  for(const auto& shape : shapes){
    for(const auto& index : shape.mesh.indices){
      Vertex vertex;
      vertex.pos = {
        attrib.vertices[3 * index.vertex_index + 0],
        attrib.vertices[3 * index.vertex_index + 1],
        attrib.vertices[3 * index.vertex_index + 2]
      };
      vertex.texCoord = {
        attrib.texcoords[2 * index.texcoord_index + 0],
        1.0f - attrib.texcoords[2 * index.texcoord_index + 1]
      };
      vertex.color = {1.0f, 1.0f, 1.0f};
      vertices.push_back(vertex);

      cloud->xyz.push_back(vertex.pos);
      cloud->rgb.push_back(vec4(1, 1, 1, 1));
      cloud->uv.push_back(vertex.texCoord);
    }
  }

  //vk_buffer->insert_model_in_engine(vertices, cloud->path_texture);
  vk_buffer->insert_cloud_in_engine(cloud);

  //---------------------------
  return cloud;
}
std::vector<VkVertexInputAttributeDescription> VK_data::vertex_attribute(){
  //---------------------------

  std::vector<VkVertexInputAttributeDescription> attributeDescriptions;

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
