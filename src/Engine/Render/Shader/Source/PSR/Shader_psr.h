#ifndef SHADER_PSR_H
#define SHADER_PSR_H

#include "struct_pyramid.h"
#include "../../../Core_common.h"

class Core_node;
class Core_param;
class Dimension;


class Shader_psr
{
public:
  Shader_psr(Core_node* node);
  ~Shader_psr();

  void update_shader();

  inline Struct_pyramid* get_pyramid_param(){return struct_pyramid;}

private:
  Core_param* core_param;
  Dimension* dimManager;

  Struct_pyramid* struct_pyramid;
};

#endif
