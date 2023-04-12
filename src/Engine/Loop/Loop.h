#ifndef LOOP_H
#define LOOP_H

class Node_engine;
class Engine_window;
class Engine_vulkan;


class Loop
{
public:
  //Constructor / Destructor
  Loop(Node_engine* node_engine);
  ~Loop();

public:
  //Main functions
  void run_loop();

private:
  Engine_window* engine_window;
  Engine_vulkan* engine_vulkan;

};

#endif
