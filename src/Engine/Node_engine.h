#ifndef NODE_ENGINE_H
#define NODE_ENGINE_H

#include "../common.h"

class Node;
class Param_engine;
class VK_engine;
class Dimension;
class Camera;
class GPU_data;
class Shader_edl;


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

  inline VK_engine* get_vk_engine(){return vk_engine;}
  inline Dimension* get_dimManager(){return dimManager;}
  inline Camera* get_cameraManager(){return cameraManager;}
  inline Param_engine* get_param_engine(){return param_engine;}
  inline GPU_data* get_gpu_data(){return gpu_data;}

private:
  Node* node;
  GPU_data* gpu_data;
  Param_engine* param_engine;
  VK_engine* vk_engine;
  Dimension* dimManager;
  Camera* cameraManager;
  Shader_edl* shader_edl;
};

#endif
