#ifndef SHADER_H
#define SHADER_H

#include "Source/EDL/struct_edl.h"
#include "Source/PSR/struct_pyramid.h"
#include "../Core_common.h"

class Core_node;
class Shader_edl;
class Shader_psr;


class Shader
{
public:
  Shader(Core_node* node);
  ~Shader();

public:

  inline Shader_edl* get_shader_edl(){return shader_edl;}
  inline Shader_psr* get_shader_psr(){return shader_psr;}

private:
  Shader_edl* shader_edl;
  Shader_psr* shader_psr;
};

#endif
