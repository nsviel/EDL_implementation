#ifndef SCENE_H
#define SCENE_H

#include "../../common.h"

class Node_engine;
class VK_buffer;


class Scene
{
public:
  //Constructor / Destructor
  Scene(Node_engine* node_engine);
  ~Scene();

public:
  //Main functions
  void load_model();

private:
  VK_buffer* vk_buffer;

  list<Set*>* list_set;
};

#endif
