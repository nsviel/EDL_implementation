#ifndef SHADER_EDL_H
#define SHADER_EDL_H

#include "struct_edl.h"
#include "../../../../common.h"

class Node_engine;
class Dimension;
class Camera;


class Shader_edl
{
public:
  Shader_edl(Node_engine* node);
  ~Shader_edl();

  void update_shader();

  inline Struct_edl* get_edl_param(){return struct_edl;}

private:
  Camera* cameraManager;
  Dimension* dimManager;

  Struct_edl* struct_edl;
};

#endif
