#ifndef SHADER_EDL_H
#define SHADER_EDL_H

#include "struct_edl.h"
#include "../../../Core_common.h"

class Core_node;
class Core_param;
class Dimension;


class Shader_edl
{
public:
  Shader_edl(Core_node* node);
  ~Shader_edl();

  void update_shader();

  inline Struct_edl* get_edl_param(){return struct_edl;}

private:
  Core_param* core_param;
  Dimension* dimManager;

  Struct_edl* struct_edl;
};

#endif
