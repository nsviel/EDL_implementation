#include "VK_error.h"

#include "../../VK_engine.h"
#include "../../VK_param.h"


//Constructor / Destructor
VK_error::VK_error(VK_engine* vk_engine){
  //---------------------------

  this->vk_engine = vk_engine;
  this->vk_param = vk_engine->get_vk_param();

  //---------------------------
}
VK_error::~VK_error(){}

//Binding error
void VK_error::uniform_name_not_recognized(Struct_binding* binding, string name){
  //---------------------------

  cout<<"------------------------"<<endl;
  cout<<"[error] Update uniform -> name not recognized \033[1;31m"<<name<<"\033[0m"<<endl;
  cout<<"Existing uniform names: "<<endl;

  for(int i=0; i<binding->vec_uniform.size(); i++){
    Struct_uniform* uniform = binding->vec_uniform[i];
    cout<<"\033[1;32m"<<uniform->name<<"\033[0m"<<endl;
  }

  cout<<"------------------------"<<endl;
  exit(0);

  //---------------------------
}
