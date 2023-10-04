#ifndef VK_DATA_H
#define VK_DATA_H

#include "../Struct/struct_pipeline.h"
#include "../Struct/struct_data.h"
#include "../../Core_common.h"

class VK_engine;
class VK_param;
class VK_buffer;
class VK_texture;
class VK_binding;
class VK_command_buffer;
class VK_descriptor;


class VK_data
{
public:
  //Constructor / Destructor
  VK_data(VK_engine* vk_engine);
  ~VK_data();

public:
  //Insertion functions
  void insert_scene_object(Object* object);
  void insert_glyph_object(Object* object);

  //Clean function
  void clean_data(Struct_data* data);
  void clean_data_all();
  void clean_data_scene(int ID);

  //Pipeline data description
  void create_data_description(Struct_pipeline* pipeline);
  void create_vertex_description(Struct_pipeline* pipeline);
  void create_attribut_description(Struct_pipeline* pipeline);
  void combine_description(Struct_pipeline* pipeline);
  void check_for_attribut(Struct_data* data);

  inline std::list<Struct_data*> get_list_data_scene(){return list_data_scene;}
  inline std::list<Struct_data*> get_list_data_glyph(){return list_data_glyph;}

private:
  VK_engine* vk_engine;
  VK_param* vk_param;
  VK_buffer* vk_buffer;
  VK_texture* vk_texture;
  VK_binding* vk_binding;
  VK_command_buffer* vk_command_buffer;
  VK_descriptor* vk_descriptor;

  std::list<Struct_data*> list_data_scene;
  std::list<Struct_data*> list_data_glyph;
};

#endif
