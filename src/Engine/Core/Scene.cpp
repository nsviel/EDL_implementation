#include "Scene.h"

#include "../Vulkan/Engine_vulkan.h"
#include "../Vulkan/Model/VK_buffer.h"
#include "../Node_engine.h"

//#define TINYOBJLOADER_IMPLEMENTATION
#include "../../../extern/tiny_obj_loader.h"


//Constructor / Destructor
Scene::Scene(Node_engine* node_engine){
  //---------------------------

  Engine_vulkan* engine_vulkan = node_engine->get_engine_vulkan();

  this->vk_buffer = engine_vulkan->get_vk_buffer();

  this->list_set = new list<Set*>();

  //---------------------------
}
Scene::~Scene(){
  //---------------------------


  //---------------------------
}

//Main function
void Scene::load_model(){
  //---------------------------

  Set* set = new Set("Viking");
  Cloud* cloud = new Cloud();
  set->list_cloud.push_back(cloud);
  list_set->push_back(set);

  const std::string MODEL_PATH = "../src/Engine/Texture/viking_room.obj";
  const std::string TEXTURE_PATH = "../src/Engine/Texture/viking_room.png";

  tinyobj::attrib_t attrib;
  std::vector<tinyobj::shape_t> shapes;
  std::vector<tinyobj::material_t> materials;
  std::string warn, err;

  bool load_ok = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, MODEL_PATH.c_str());
  if(!load_ok){
    throw std::runtime_error(warn + err);
  }

  for (const auto& shape : shapes) {
    for (const auto& index : shape.mesh.indices) {
      vec3 xyz = {
        attrib.vertices[3 * index.vertex_index + 0],
        attrib.vertices[3 * index.vertex_index + 1],
        attrib.vertices[3 * index.vertex_index + 2]
      };

      vec2 uv = {
        attrib.texcoords[2 * index.texcoord_index + 0],
        1.0f - attrib.texcoords[2 * index.texcoord_index + 1]
      };

      vec4 rgb = {1.0f, 1.0f, 1.0f, 1.0f};

      cloud->xyz.push_back(xyz);
      cloud->uv.push_back(uv);
      cloud->rgb.push_back(rgb);
    }
  }


  //vk_buffer->create_vertex_buffer(cloud->xyz);

  //---------------------------
}
