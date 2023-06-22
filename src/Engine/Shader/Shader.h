#ifndef SHADER_H
#define SHADER_H

#include "../../common.h"

class Node_engine;
class Shader_edl;
class Shader_psr;


class Shader
{
public:
  Shader(Node_engine* node);
  ~Shader();

public:

  inline Shader_edl* get_shader_edl(){return shader_edl;}
  inline Shader_psr* get_shader_psr(){return shader_psr;}

private:
  Shader_edl* shader_edl;
  Shader_psr* shader_psr;
};

#endif
