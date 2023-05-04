#ifndef NODE_ENGINE_H
#define NODE_ENGINE_H

class Engine_vulkan;
class Loop;
class Scene;
class Dimension;

class Node_load;
class Node_gui;


class Node_engine
{
public:
  //Constructor / Destructor
  Node_engine();
  ~Node_engine();

public:
  void loop();
  
  inline Engine_vulkan* get_engine_vulkan(){return engine_vulkan;}
  inline Loop* get_engine_loop(){return engine_loop;}
  inline Dimension* get_dimManager(){return dimManager;}

  inline Node_gui* get_node_gui(){return node_gui;}

private:
  Engine_vulkan* engine_vulkan;
  Loop* engine_loop;
  Scene* sceneManager;
  Dimension* dimManager;

  Node_load* node_load;
  Node_gui* node_gui;
};

#endif
