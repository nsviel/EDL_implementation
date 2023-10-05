#ifndef NODE_CORE_H
#define NODE_CORE_H

#include "../common.h"

class Node;
class Render_param;
class VK_engine;
class Dimension;
class Camera;
class GPU_data;
class Shader;
class Window;


class Render_node
{
public:
  //Constructor / Destructor
  Render_node(Node* node);
  ~Render_node();

public:
  void init(Window* window);
  void loop_start();
  void loop();
  void exit();
  void reset();

  inline Node* get_node(){return node;}

  inline VK_engine* get_vk_engine(){return vk_engine;}
  inline Dimension* get_dimManager(){return dimManager;}
  inline Camera* get_cameraManager(){return cameraManager;}
  inline Render_param* get_core_param(){return core_param;}
  inline GPU_data* get_gpu_data(){return gpu_data;}
  inline Shader* get_shaderManager(){return shaderManager;}

private:
  Node* node;
  GPU_data* gpu_data;
  Render_param* core_param;
  VK_engine* vk_engine;
  Dimension* dimManager;
  Camera* cameraManager;
  Shader* shaderManager;
};

#endif
