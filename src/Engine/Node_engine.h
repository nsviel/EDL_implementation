#ifndef NODE_ENGINE_H
#define NODE_ENGINE_H

class Engine_vulkan;
class Loop;
class GUI;
class Scene;
class Dimension;
class Node_load;


class Node_engine
{
public:
  //Constructor / Destructor
  Node_engine();
  ~Node_engine();

public:
  inline Engine_vulkan* get_engine_vulkan(){return engine_vulkan;}
  inline Loop* get_engine_loop(){return engine_loop;}
  inline GUI* get_guiManager(){return guiManager;}
  inline Dimension* get_dimManager(){return dimManager;}

private:
  Engine_vulkan* engine_vulkan;
  Loop* engine_loop;
  GUI* guiManager;
  Scene* sceneManager;
  Dimension* dimManager;

  Node_load* node_load;
};

#endif
