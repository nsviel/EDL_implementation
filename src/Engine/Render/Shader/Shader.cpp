#include "Shader.h"

#include "Source/EDL/Shader_edl.h"
#include "Source/PSR/Shader_psr.h"


Shader::Shader(Render_node* node){
  //---------------------------

  this->shader_edl = new Shader_edl(node);
  this->shader_psr = new Shader_psr(node);

  //---------------------------
}
Shader::~Shader(){
  //---------------------------

  delete shader_edl;
  delete shader_psr;

  //---------------------------
}
