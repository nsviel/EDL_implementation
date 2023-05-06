#ifndef NODE_ENGINE_H
#define NODE_ENGINE_H

#include "../common.h"

class Node;
class Engine;
class Scene;
class Dimension;
class Control;
class Camera;


class Node_engine
{
public:
  //Constructor / Destructor
  Node_engine(Node* node);
  ~Node_engine();

public:
  void init();
  void loop();
  void exit();

  inline Engine* get_engineManager(){return engineManager;}
  inline Dimension* get_dimManager(){return dimManager;}
  inline Control* get_controlManager(){return controlManager;}
  inline Camera* get_cameraManager(){return cameraManager;}

private:
  Node* node;
  Engine* engineManager;
  Scene* sceneManager;
  Dimension* dimManager;
  Control* controlManager;
  Camera* cameraManager;
};

#endif
