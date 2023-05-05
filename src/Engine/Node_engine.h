#ifndef NODE_ENGINE_H
#define NODE_ENGINE_H

class Engine_vulkan;
class Scene;
class Dimension;
class Control;
class Camera;

class Node_load;
class Node_gui;


class Node_engine
{
public:
  //Constructor / Destructor
  Node_engine();
  ~Node_engine();

public:
  void init();
  void loop();

  inline Engine_vulkan* get_engine_vulkan(){return engine_vulkan;}
  inline Dimension* get_dimManager(){return dimManager;}
  inline Control* get_controlManager(){return controlManager;}
  inline Camera* get_cameraManager(){return cameraManager;}

  inline Node_gui* get_node_gui(){return node_gui;}

private:
  Engine_vulkan* engine_vulkan;
  Scene* sceneManager;
  Dimension* dimManager;
  Control* controlManager;
  Camera* cameraManager;

  Node_load* node_load;
  Node_gui* node_gui;
};

#endif
