#ifndef ENGINE_H
#define ENGINE_H

class Node_engine;
class Engine_window;
class Engine_vulkan;
class Loop;


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
  Engine_window* engine_window;
  Engine_vulkan* engine_vulkan;
  Loop* engine_loop;
};

#endif
