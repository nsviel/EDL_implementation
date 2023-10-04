#include "Attribut.h"


// Constructor / Destructor
Attribut::Attribut(){}
Attribut::~Attribut(){}

//Main function
void Attribut::compute_MinMax(Object* object){
  vector<vec3>& XYZ = object->xyz;
  vec3 centroid = vec3(0, 0, 0);
  vec3 min = XYZ[0];
  vec3 max = XYZ[0];
  //---------------------------

  for(int i=0; i<XYZ.size(); i++){
    for(int j=0; j<3; j++){
      if(XYZ[i][j] <= min[j]) min[j] = XYZ[i][j];
      if(XYZ[i][j] >= max[j]) max[j] = XYZ[i][j];
      centroid[j] += XYZ[i][j];
    }
  }

  for(int j=0;j<3;j++){
    centroid[j] /= XYZ.size();
  }

  //---------------------------
  object->min = min;
  object->max = max;
  object->COM = centroid;
}
void Attribut::set_visibility(Set* set, bool visibility){
  //---------------------------

  for(int i=0; i<set->list_obj.size(); i++){
    Object* object = *next(set->list_obj.begin(), i);
    object->is_visible = visibility;
  }

  //---------------------------
}
