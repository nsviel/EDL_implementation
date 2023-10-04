#include <Specific/Struct/struct_object.h>


void Object::reset(){
  //---------------------------

  this->min = glm::vec3(0.0f);
  this->max = glm::vec3(0.0f);
  this->root = glm::vec3(0.0f);
  this->COM = glm::vec3(0.0f);

  this->rotat = glm::mat4(1.0f);
  this->trans = glm::mat4(1.0f);
  this->scale = glm::mat4(1.0f);
  this->model = glm::mat4(1.0f);
  this->mvp = glm::mat4(1.0f);


  //---------------------------
}
