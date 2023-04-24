#ifndef ENGINE_H
#define ENGINE_H

class Node_engine;
class Engine_vulkan;
class Loop;
class GUI;


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
  Loop* engine_loop;
  GUI* guiManager;
};

#endif
