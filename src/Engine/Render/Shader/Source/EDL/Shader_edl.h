#ifndef SHADER_EDL_H
#define SHADER_EDL_H

#include "struct_edl.h"
#include <Specific/common.h>

class Render_node;
class Render_param;
class Window;


class Shader_edl
{
public:
  Shader_edl(Render_node* node);
  ~Shader_edl();

  void update_shader();

  inline Struct_edl* get_edl_param(){return struct_edl;}

private:
  Render_param* core_param;
  Window* window;

  Struct_edl* struct_edl;
};

#endif
