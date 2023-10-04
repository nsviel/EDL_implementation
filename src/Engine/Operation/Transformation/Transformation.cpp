#include "Transformation.h"

#include <Specific/Function/fct_math.h>


// Constructor / Destructor
Transformation::Transformation(){}
Transformation::~Transformation(){}

// Translation
void Transformation::make_translation(Object* object, vec3 trans){
  if(object == nullptr) return;
  //---------------------------

  glm::mat4 translation = get_translation_mat(trans);

  object->COM += trans;
  object->trans *= translation;
  object->model *= translation;

  //---------------------------
}

//Rotation
void Transformation::make_rotation(Object* object, vec3 COM, vec3 radian){
  if(object == nullptr) return;
  //---------------------------

  mat4 rotation = get_rotation_mat(radian);
  mat4 COM_mat = get_translation_mat_neye(COM);

  object->model -= COM_mat;
  object->model *= rotation;
  object->model += COM_mat;

  //---------------------------
}

//Scaling
void Transformation::make_scaling(Object* object, float scale){
  if(object == nullptr) return;
  //---------------------------

  glm::mat4 scaling(1.0);
  scaling[0][0] = scale;
  scaling[1][1] = scale;
  scaling[2][2] = scale;

  object->scale *= scaling;
  object->model *= scaling;

  //---------------------------
}

//Transformation
mat4 Transformation::get_translation_mat(vec3 trans){
  glm::mat4 translation(1.0);
  //---------------------------

  translation[0][3] = trans.x;
  translation[1][3] = trans.y;
  translation[2][3] = trans.z;

  //---------------------------
  return translation;
}
mat4 Transformation::get_translation_mat_neye(vec3 trans){
  glm::mat4 translation(0.0);
  //---------------------------

  translation[0][3] = trans.x;
  translation[1][3] = trans.y;
  translation[2][3] = trans.z;

  //---------------------------
  return translation;
}
mat4 Transformation::get_rotation_mat(vec3 r){
  glm::mat4 Rx(1.0);
  glm::mat4 Ry(1.0);
  glm::mat4 Rz(1.0);
  //---------------------------

  Rx[1][1]=cos(r.x);
  Rx[2][1]=sin(r.x);
  Rx[1][2]=-sin(r.x);
  Rx[2][2]=cos(r.x);

  Ry[0][0]=cos(r.y);
  Ry[0][2]=sin(r.y);
  Ry[2][0]=-sin(r.y);
  Ry[2][2]=cos(r.y);

  Rz[0][0]=cos(r.z);
  Rz[1][0]=sin(r.z);
  Rz[0][1]=-sin(r.z);
  Rz[1][1]=cos(r.z);

  glm::mat4 rotation = Rx * Ry * Rz;

  //---------------------------
  return rotation;
}
