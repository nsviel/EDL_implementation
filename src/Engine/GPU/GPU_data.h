#ifndef GPU_DATA_H
#define GPU_DATA_H

#include "../../common.h"

class Node_engine;
class VK_texture;
class VK_buffer;
class VK_descriptor;
class VK_command;


class GPU_data
{
public:
  //Constructor / Destructor
  GPU_data(Node_engine* node_engine);
  ~GPU_data();

public:
  //Insert function
  void insert_object_for_drawing(Object* object);
  void insert_object_in_engine(Object* object);

  //Remove function
  void remove_object_for_drawing(Object* object);

private:
  VK_texture* vk_texture;
  VK_buffer* vk_buffer;
  VK_descriptor* vk_descriptor;
  VK_command* vk_command;

  std::list<Object*> list_draw;
};

#endif