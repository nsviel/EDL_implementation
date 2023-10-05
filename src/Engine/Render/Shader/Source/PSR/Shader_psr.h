#ifndef SHADER_PSR_H
#define SHADER_PSR_H

#include "struct_pyramid.h"
#include "../../../Render_common.h"

class Render_node;
class Render_param;
class Dimension;


class Shader_psr
{
public:
  Shader_psr(Render_node* node);
  ~Shader_psr();

  void update_shader();

  inline Struct_pyramid* get_pyramid_param(){return struct_pyramid;}

private:
  Render_param* core_param;
  Dimension* dimManager;

  Struct_pyramid* struct_pyramid;
};

#endif
