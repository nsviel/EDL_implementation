#include "Control.h"
#include "Scene.h"

#include "../Data_node.h"

#include "../../Core/Dimension/Dimension.h"
#include "../../Core/Camera/Camera.h"
#include "../../Core/Core_node.h"
#include <Operation/Transformation/Transformation.h>
#include "../../Node.h"


//Constructor / Destructor
Control::Control(Data_node* data_node){
  //---------------------------

  this->node = data_node->get_node();
  Core_node* core_node = data_node->get_core_node();
  this->dimManager = core_node->get_dimManager();
  this->cameraManager = core_node->get_cameraManager();
  this->sceneManager = data_node->get_sceneManager();

  //---------------------------
}
Control::~Control(){}

//Main function
void Control::exit(){
  GLFWwindow* window = dimManager->get_window();
  //---------------------------

  glfwSetWindowShouldClose(window, true);

  //---------------------------
}
void Control::reset(){
  //---------------------------

  node->reset();

  //---------------------------
}

//Selected object function
void Control::selected_object_translation(vec3 translation){
  Set* set_object = sceneManager->get_set_scene();
  //---------------------------

  Transformation transformManager;
  transformManager.make_translation(set_object->selected_obj, translation);

  //---------------------------
}
void Control::selected_object_rotation(vec3 rotation){
  Set* set_object = sceneManager->get_set_scene();
  //---------------------------

  Transformation transformManager;
  Object* object = set_object->selected_obj;
  transformManager.make_rotation(object, object->COM, rotation);

  //---------------------------
}
void Control::selected_object_deletion(){
  Set* set_object = sceneManager->get_set_scene();
  //----------------------------

  Object* object = set_object->selected_obj;
  this->selected_object_next();
  sceneManager->delete_scene_object(object);

  //----------------------------
}
void Control::object_deletion(Object* object){
  //----------------------------

  //this->selected_object_next();
  sceneManager->delete_scene_object(object);

  //----------------------------
}
void Control::selected_object_next(){
  Set* set_object = sceneManager->get_set_scene();
  Object* selected = set_object->selected_obj;
  //----------------------------

  for(int i=0; i<set_object->list_obj.size(); i++){
    Object* object = *next(set_object->list_obj.begin(), i);

    if(selected->ID == object->ID){
      Object* selection;

      if((i + 1) < set_object->list_obj.size()){
        selection = *next(set_object->list_obj.begin(), i + 1);
      }else{
        selection = *next(set_object->list_obj.begin(), 0);
      }

      set_object->selected_obj = selection;
    }
  }

  //----------------------------
}
