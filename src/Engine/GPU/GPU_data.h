#ifndef GPU_DATA_H
#define GPU_DATA_H

#include "../../common.h"

class Node_engine;
class VK_texture;
class VK_buffer;
class VK_descriptor;
class VK_command;
class VK_data;


class GPU_data
{
public:
  //Constructor / Destructor
  GPU_data(Node_engine* node_engine);
  ~GPU_data();

public:
  //Main function
  void insert_object_in_engine(Object* object);
  void loop_check_descriptor_update();

  //Subfunctions
  void create_object_buffer(Object* object);
  void remove_object_for_drawing(Object* object);
  void update_descriptor_set();

private:
  VK_texture* vk_texture;
  VK_buffer* vk_buffer;
  VK_descriptor* vk_descriptor;
  VK_command* vk_command;
  VK_data* vk_data;

  std::list<Object*> list_draw;
  bool is_descriptor_up;
};

#endif
