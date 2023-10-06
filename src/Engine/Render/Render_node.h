#ifndef NODE_CORE_H
#define NODE_CORE_H

#include "../common.h"

class Engine;
class Render_param;
class VK_engine;
class Camera;
class GPU_data;
class Shader;
class Window;


class Render_node
{
public:
  //Constructor / Destructor
  Render_node(Engine* engine);
  ~Render_node();

public:
  void init();
  void loop_start();
  void loop();
  void exit();
  void reset();

  inline Engine* get_engine(){return engine;}

  inline VK_engine* get_vk_engine(){return vk_engine;}
  inline Camera* get_cameraManager(){return cameraManager;}
  inline Render_param* get_core_param(){return core_param;}
  inline GPU_data* get_gpu_data(){return gpu_data;}
  inline Shader* get_shaderManager(){return shaderManager;}
  inline Window* get_window(){return window;}

private:
  Engine* engine;
  GPU_data* gpu_data;
  Render_param* core_param;
  VK_engine* vk_engine;
  Camera* cameraManager;
  Shader* shaderManager;
  Window* window;
};

#endif
