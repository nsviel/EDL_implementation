#include "Control.h"
#include "../Node_gui.h"
#include "../../Data/Scene/Scene.h"

#include "../../Data/Data_node.h"

#include "../../Render/Dimension/Dimension.h"
#include "../../Render/Camera/Camera.h"
#include "../../Render/Render_node.h"
#include <Operation/Transformation/Transformation.h>
#include "../../Node.h"


//Constructor / Destructor
Control::Control(Node_gui* gui_node){
  //---------------------------

  this->node = gui_node->get_node();
  Render_node* core_node = gui_node->get_core_node();
  Data_node* data_node = gui_node->get_data_node();
  this->dimManager = core_node->get_dimManager();
  this->cameraManager = core_node->get_cameraManager();
  this->sceneManager = data_node->get_sceneManager();
  this->transformManager = new Transformation();

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
  Set* set = sceneManager->get_set_scene();
  //---------------------------

  transformManager->make_translation(set->selected_obj, translation);

  //---------------------------
}
void Control::selected_object_rotation(vec3 rotation){
  Set* set = sceneManager->get_set_scene();
  //---------------------------

  Object* object = set->selected_obj;
  transformManager->make_rotation(object, object->COM, rotation);

  //---------------------------
}
void Control::selected_object_deletion(){
  Set* set = sceneManager->get_set_scene();
  //----------------------------

  Object* object = set->selected_obj;
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
  Set* set = sceneManager->get_set_scene();
  Object* selected = set->selected_obj;
  //----------------------------

  for(int i=0; i<set->list_obj.size(); i++){
    Object* object = *next(set->list_obj.begin(), i);

    if(selected->ID == object->ID){
      Object* selection;

      if((i + 1) < set->list_obj.size()){
        selection = *next(set->list_obj.begin(), i + 1);
      }else{
        selection = *next(set->list_obj.begin(), 0);
      }

      set->selected_obj = selection;
    }
  }

  //----------------------------
}
