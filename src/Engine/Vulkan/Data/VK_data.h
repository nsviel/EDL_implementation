#ifndef VK_DATA_H
#define VK_DATA_H

#include "../Struct/struct_pipeline.h"
#include "../../../common.h"

class Engine;
class Param_vulkan;
class VK_device;
class VK_buffer;
class VK_texture;


class VK_data
{
public:
  //Constructor / Destructor
  VK_data(Engine* engineManager);
  ~VK_data();

public:
  //Main functions
  void cleanup();
  void clean_object(Object* object);

  //Pipeline data description
  void create_pipeline_data(Struct_pipeline* pipeline);
  void create_vertex_description(Struct_pipeline* pipeline);
  void create_data_description(Struct_pipeline* pipeline);
  void combine_description(Struct_pipeline* pipeline);

  inline void set_list_data(std::list<Object*> value){this->list_data = value;}
  inline void set_list_glyph(std::list<Object*> value){this->list_glyph = value;}
  inline std::list<Object*> get_list_data(){return list_data;}
  inline std::list<Object*> get_list_glyph(){return list_glyph;}

private:
  Engine* engineManager;
  Param_vulkan* param_vulkan;
  VK_device* vk_device;
  VK_buffer* vk_buffer;
  VK_texture* vk_texture;

  std::list<Object*> list_data;
  std::list<Object*> list_glyph;
};

#endif
