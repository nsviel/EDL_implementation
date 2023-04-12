#ifndef NODE_ENGINE_H
#define NODE_ENGINE_H

class Engine_window;
class Engine_vulkan;
class Loop;


class Node_engine
{
public:
  //Constructor / Destructor
  Node_engine();
  ~Node_engine();

public:
  inline Engine_window* get_engine_window(){return engine_window;}
  inline Engine_vulkan* get_engine_vulkan(){return engine_vulkan;}
  inline Loop* get_engine_loop(){return engine_loop;}

private:
  Engine_window* engine_window;
  Engine_vulkan* engine_vulkan;
  Loop* engine_loop;
};

#endif
