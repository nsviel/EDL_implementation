#include "Shader_edl.h"

#include "../../../Node_engine.h"
#include "../../../Dimension/Dimension.h"


Shader_edl::Shader_edl(Node_engine* node){
  //---------------------------

  this->dimManager = node->get_dimManager();

  this->with_edl = true;
  this->edl_strength = 100.0;
  this->edl_distance = 1.0;
  this->edl_radius = 1.0;
  //this->clip_far = configManager->parse_json_f("camera", "clip_far");
  //this->clip_near = configManager->parse_json_f("camera", "clip_near");

  //---------------------------
}
Shader_edl::~Shader_edl(){}

void Shader_edl::setup_shader(){
  //---------------------------

  // Setup shader parameters
  auto a = (clip_far + clip_near) / (clip_far - clip_near);
  auto b = (-2 * clip_far * clip_near) / (clip_far - clip_near);
  /*shader->setFloat("A", a);
  shader->setFloat("B", b);

  shader->setFloat("EDL_STRENGTH", edl_strength);
  shader->setFloat("EDL_DISTANCE", edl_distance);
  shader->setFloat("EDL_RADIUS", edl_radius);
  shader->setInt("EDL_ON", with_edl);

  vec2 gl_dim = dimManager->get_gl_dim();
  shader->setInt("GL_WIDTH", gl_dim.x);
  shader->setInt("GL_HEIGHT", gl_dim.y);*/

  //---------------------------
}
