#ifndef SHADER_PSR_H
#define SHADER_PSR_H

#include "struct_pyramid.h"
#include "../../../../common.h"

class Node_engine;
class Param_engine;
class Dimension;


class Shader_psr
{
public:
  Shader_psr(Node_engine* node);
  ~Shader_psr();

  void update_shader();

  inline Struct_pyramid* get_pyramid_param(){return struct_pyramid;}

private:
  Param_engine* param_engine;
  Dimension* dimManager;

  Struct_pyramid* struct_pyramid;
};

#endif
