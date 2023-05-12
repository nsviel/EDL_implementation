#include "Transformation.h"

#include "../../Specific/Function/fct_math.h"


// Constructor / Destructor
Transformation::Transformation(){}
Transformation::~Transformation(){}

// Translation
void Transformation::make_translation(Object* object, vec3 trans){
  //---------------------------

  glm::mat4 translation = get_translation_mat(trans);

  object->COM += trans;
  object->trans *= translation;
  object->model *= translation;

  //---------------------------
}
void Transformation::make_translation(vector<vec3>& XYZ, vec3 trans){
  //Translation matrice creation
  glm::mat4 translation(1.0);
  //---------------------------

  translation[0][3] = trans.x;
  translation[1][3] = trans.y;
  translation[2][3] = trans.z;

  //Apply
  //this->make_Transformation_atomic(XYZ, vec3(0, 0, 0), translation);

  //---------------------------
}

//Rotation
void Transformation::make_rotation(Object* object, vec3 COM, vec3 radian){
  //---------------------------

  mat4 rotation = get_rotation_mat(radian);
  mat4 COM_mat = get_translation_mat_neye(COM);

  object->model -= COM_mat;
  object->model *= rotation;
  object->model += COM_mat;

  //---------------------------
}

//Subfunction
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
