#ifndef GPU_DATA_H
#define GPU_DATA_H

#include "../../common.h"

class Node_engine;
class VK_texture;
class VK_buffer;


class GPU_data
{
public:
  //Constructor / Destructor
  GPU_data(Node_engine* node_engine);
  ~GPU_data();

public:
  void draw_object(Object* object);
  void insert_object_in_engine(Object* object);

private:
  VK_texture* vk_texture;
  VK_buffer* vk_buffer;
};

#endif
