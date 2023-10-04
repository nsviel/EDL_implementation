#ifndef GPU_DATA_H
#define GPU_DATA_H

#include "../Core_common.h"

class Core_node;
class VK_texture;
class VK_buffer;
class VK_descriptor;
class VK_command;
class VK_data;


class GPU_data
{
public:
  //Constructor / Destructor
  GPU_data(Core_node* core_node);
  ~GPU_data();

public:
  //Main function
  void insert_object_in_engine(Object* object);
  void insert_glyph_in_engine(Object* object);
  void remove_object_in_engine(Object* object);

  inline bool* get_update_scene(){return &update_scene;}

private:
  VK_texture* vk_texture;
  VK_buffer* vk_buffer;
  VK_descriptor* vk_descriptor;
  VK_command* vk_command;
  VK_data* vk_data;

  std::list<Object*> list_scene;
  std::list<Object*> list_glyph;
  bool update_scene;
};

#endif
