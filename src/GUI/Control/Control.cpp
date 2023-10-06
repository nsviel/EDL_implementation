#include "Control.h"
#include <GUI_node.h>
#include <Data/Scene/Scene.h>
#include <Data/Data_node.h>
#include <Camera/Camera.h>
#include <Render/Render_node.h>
#include <Engine.h>

#include <Operation/Transformation/Transformation.h>
#include <Window/Window.h>


//Constructor / Destructor
Control::Control(GUI_node* gui_node){
  //---------------------------

  this->engine = gui_node->get_engine();
  Render_node* render_node = gui_node->get_node_render();
  Data_node* data_node = gui_node->get_data_node();
  this->window = gui_node->get_window();
  this->cameraManager = render_node->get_cameraManager();
  this->sceneManager = data_node->get_sceneManager();
  this->transformManager = new Transformation();

  //---------------------------
}
Control::~Control(){}

//Main function
void Control::exit(){
  //---------------------------

  window->close_window();

  //---------------------------
}
void Control::reset(){
  //---------------------------

  engine->reset();

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
