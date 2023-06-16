#include "Setfunc.h"


//ConsScenetor / DesScenetor
Setfunc::Setfunc(){
  //---------------------------


  //---------------------------
}
Setfunc::~Setfunc(){}

//Main function
void Setfunc::set_visibility(Set* set, bool visibility){
  //---------------------------

  for(int i=0; i<set->list_obj.size(); i++){
    Object* object = *next(set->list_obj.begin(), i);
    object->is_visible = visibility;
  }

  //---------------------------
}
