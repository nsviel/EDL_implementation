#include "GUI_mouse.h"

#include <GUI.h>

#include <Render/Render_node.h>
#include <Render/Render_param.h>
#include <Camera/Camera.h>
#include <Specific/Function/fct_math.h>
#include <Data/Data_node.h>
#include <Data/Scene/Scene.h>
#include <Engine.h>
#include <Operation/Transformation/Transformation.h>
#include <Window/Window.h>


//Constructor / Destructor
GUI_mouse::GUI_mouse(GUI* gui){
  //---------------------------

  Render_node* render_node = gui->get_node_render();
  Data_node* data_node = gui->get_data_node();
  this->core_param = render_node->get_core_param();
  this->window = render_node->get_window();
  this->cameraManager = render_node->get_cameraManager();
  this->transformManager = new Transformation();
  this->sceneManager = data_node->get_sceneManager();

  //---------------------------
}
GUI_mouse::~GUI_mouse(){}

//Main function
void GUI_mouse::run_control(ImVec2 center){
  //---------------------------

  this->control_mouse(center);
  this->control_mouse_wheel();

  //---------------------------
}

//Mouse function
void GUI_mouse::control_mouse(ImVec2 center){
  ImGuiIO io = ImGui::GetIO();
  Struct_camera* camera = &core_param->camera;
  //----------------------------

  window->set_window_center(vec2(center.x, center.y));

  //Right click - Camera movement
  static vec2 cursorPos;
  if(ImGui::IsMouseClicked(1)){
    cursorPos = window->get_mouse_pose();

    ImGui::GetIO().MouseDrawCursor = false;
    window->set_mouse_pose(vec2(center.x, center.y));
    camera->cam_move = true;
  }
  //Release - back to normal
  if(ImGui::IsMouseReleased(1) && camera->cam_move){
    window->set_mouse_pose(cursorPos);
    camera->cam_move = false;
  }

  //---------------------------
}
void GUI_mouse::control_mouse_wheel(){
  static int wheel_mode = 0;
  ImGuiIO io = ImGui::GetIO();
  //----------------------------

  //Wheel + right clicked - Camera zoom
  if(io.MouseWheel && io.MouseDownDuration[1] >= 0.0f){
    cameraManager->compute_zoom(io.MouseWheel);
  }

  //Wheel click - Change mouse wheel mode
  if(ImGui::IsMouseClicked(2)){
    wheel_mode++;
    if(wheel_mode >= 3) wheel_mode = 0;
  }

  //Wheel actions
  if(io.MouseWheel && io.MouseDownDuration[1] == -1){
    //Rotation quantity
    float radian = 5 * M_PI/180;
    vec3 R;
    if(wheel_mode == 0){
      R = vec3(0, 0, fct_sign(io.MouseWheel) * radian);
    }
    else if(wheel_mode == 1){
      R = vec3(0, fct_sign(io.MouseWheel) * radian, 0);
    }
    else if(wheel_mode == 2){
      R = vec3(fct_sign(io.MouseWheel) * radian, 0, 0);
    }

    //Apply rotation
    Set* set = sceneManager->get_set_scene();
    Object* object = set->selected_obj;
    transformManager->make_rotation(object, object->COM, R);
  }

  //----------------------------
}
