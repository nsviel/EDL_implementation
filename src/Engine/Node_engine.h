#ifndef NODE_ENGINE_H
#define NODE_ENGINE_H

#include "../common.h"

class Node;
class Param_engine;
class Engine;
class Dimension;
class Camera;
class GPU_data;


class Node_engine
{
public:
  //Constructor / Destructor
  Node_engine(Node* node);
  ~Node_engine();

public:
  void init();
  void loop_start();
  void loop();
  void exit();
  void reset();

  inline Node* get_node(){return node;}

  inline Engine* get_engineManager(){return engineManager;}
  inline Dimension* get_dimManager(){return dimManager;}
  inline Camera* get_cameraManager(){return cameraManager;}
  inline Param_engine* get_param_engine(){return param_engine;}
  inline GPU_data* get_gpu_data(){return gpu_data;}

private:
  Node* node;
  GPU_data* gpu_data;
  Param_engine* param_engine;
  Engine* engineManager;
  Dimension* dimManager;
  Camera* cameraManager;
};

#endif
