#ifndef VK_DATA_H
#define VK_DATA_H

#include "../Struct/struct_pipeline.h"
#include "../Struct/struct_data.h"
#include "../../../common.h"

class Engine;
class Param_vulkan;
class VK_device;
class VK_buffer;
class VK_descriptor;
class VK_texture;
class VK_uniform;


class VK_data
{
public:
  //Constructor / Destructor
  VK_data(Engine* engineManager);
  ~VK_data();

public:
  //Insertion functions
  void insert_scene_object(Object* object);
  void insert_glyph_object(Object* object);

  //Clean function
  void cleanup();
  void clean_data(Struct_data* data);
  void clean_data(int ID);

  //Pipeline data description
  void create_data_description(Struct_pipeline* pipeline);
  void create_vertex_description(Struct_pipeline* pipeline);
  void create_attribut_description(Struct_pipeline* pipeline);
  void combine_description(Struct_pipeline* pipeline);
  void check_for_attribut(Struct_data* data);

  inline std::list<Struct_data*> get_list_data_scene(){return list_data_scene;}
  inline std::list<Struct_data*> get_list_data_glyph(){return list_data_glyph;}

private:
  Engine* engineManager;
  Param_vulkan* param_vulkan;
  VK_device* vk_device;
  VK_buffer* vk_buffer;
  VK_texture* vk_texture;
  VK_uniform* vk_uniform;
  VK_descriptor* vk_descriptor;

  std::list<Struct_data*> list_data_scene;
  std::list<Struct_data*> list_data_glyph;
};

#endif
