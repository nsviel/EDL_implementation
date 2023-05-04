#ifndef ENGINE_H
#define ENGINE_H

#include "../../common.h"

class Node_engine;
class Engine_vulkan;


class Engine
{
public:
  //Constructor / Destructor
  Engine();
  ~Engine();

public:
  //Main functions
  void init_engine();
  void loop();
  void cleanup();

private:
  Node_engine* node_engine;
  Engine_vulkan* engine_vulkan;
};

#endif
