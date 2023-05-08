#include "Loader.h"

#include "../Format/PLY/PLY_importer.h"

#include "../../Engine/Node_engine.h"
#include "../../Engine/GPU/GPU_data.h"
#include "../../Node.h"

#include "../../../extern/tiny_obj_loader.h"


//Constructor / Destructor
Loader::Loader(Node* node){
  //---------------------------

  Node_engine* node_engine = node->get_node_engine();
  this->gpu_data = node_engine->get_gpu_data();
  this->plyManager = new PLY_importer();

  //---------------------------
}
Loader::~Loader(){
  //---------------------------

  delete plyManager;

  //---------------------------
}

//Main functions
Cloud* Loader::load_cloud(string path){
  Cloud* cloud = new Cloud();
  //---------------------------

  //Check file existence
  if(is_file_exist(path) == false){
    string log = "File doesn't exists: "+ path;
  }

  //Load file data
  Data* data = plyManager->Loader(path);

  cloud->name = data->name;
  cloud->xyz = data->xyz;
  cloud->rgb = data->rgb;

  //Delete raw data
  delete data;

  //---------------------------
  return cloud;
}
Object* Loader::load_object(string path){
  //---------------------------

  Object* object = new Object();
  object->path_file = path;
  object->path_text = "../src/Engine/Texture/viking_room.png";
  object->draw_type_name = "point";
  object->has_texture = true;

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

//Subfunctions
bool Loader::is_file_exist(std::string path){
  //---------------------------

  std::ifstream infile(path.c_str());

  //---------------------------
  return infile.good();
}
