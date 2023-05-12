#include "Transformation.h"

#include "../../Specific/Function/fct_math.h"


// Constructor / Destructor
Transformation::Transformation(){}
Transformation::~Transformation(){}

// Translation
void Transformation::make_translation(Object* object, vec3 trans){
  //Translation matrice creation
  glm::mat4 translation(1.0);
  //---------------------------

  translation[0][3] = trans.x;
  translation[1][3] = trans.y;
  translation[2][3] = trans.z;

  //---------------------------
  object->trans *= translation;
  object->model *= translation;
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
  //Rotation matrice creation - rx, ry, rz are in radian
  glm::mat4 Rx(1.0);
  glm::mat4 Ry(1.0);
  glm::mat4 Rz(1.0);
  //---------------------------

  float rx = radian.x;
  float ry = radian.y;
  float rz = radian.z;

  Rx[1][1]=cos(rx);
  Rx[2][1]=sin(rx);
  Rx[1][2]=-sin(rx);
  Rx[2][2]=cos(rx);

  Ry[0][0]=cos(ry);
  Ry[0][2]=sin(ry);
  Ry[2][0]=-sin(ry);
  Ry[2][2]=cos(ry);

  Rz[0][0]=cos(rz);
  Rz[1][0]=sin(rz);
  Rz[0][1]=-sin(rz);
  Rz[1][1]=cos(rz);

  glm::mat4 rotation = Rx * Ry * Rz;

  //---------------------------
  object->model *= rotation;
}
