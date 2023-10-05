#include "GUI_control.h"

#include "../Node_gui.h"

#include "../../Render/Render_node.h"
#include "../../Render/Render_param.h"
#include "../../../Element/Window/Dimension.h"
#include "../../Render/Camera/Camera.h"
#include <Specific/Function/fct_math.h>
#include "Control.h"
#include "../../Data/Data_node.h"
#include "../../Node.h"


//Constructor / Destructor
GUI_control::GUI_control(Node_gui* node_gui){
  //---------------------------

  Render_node* core_node = node_gui->get_core_node();
  this->core_param = core_node->get_core_param();
  this->dimManager = core_node->get_dimManager();
  this->cameraManager = core_node->get_cameraManager();
  this->controlManager = node_gui->get_controlManager();

  //---------------------------
}
GUI_control::~GUI_control(){}

//Main function
void GUI_control::make_control(ImVec2 center){
  //---------------------------

  this->control_mouse(center);
  this->control_mouse_wheel();
  this->control_keyboard_oneAction();
  this->control_keyboard_camMove();
  this->control_keyboard_translation();

  //---------------------------
}

//Mouse function
void GUI_control::control_mouse(ImVec2 center){
  Tab* tab_rendering = dimManager->get_tab("rendering");
  ImGuiIO io = ImGui::GetIO();
  Struct_camera* camera = &core_param->camera;
  //----------------------------

  tab_rendering->center = vec2(center.x, center.y);

  //Right click - Camera movement
  static vec2 cursorPos;
  if(ImGui::IsMouseClicked(1)){
    cursorPos = dimManager->get_mouse_pose();

    ImGui::GetIO().MouseDrawCursor = false;
    dimManager->set_mouse_pose(vec2(center.x, center.y));
    camera->cam_move = true;
  }
  //Release - back to normal
  if(ImGui::IsMouseReleased(1) && camera->cam_move){
    dimManager->set_mouse_pose(cursorPos);
    camera->cam_move = false;
  }

  //---------------------------
}
void GUI_control::control_mouse_wheel(){
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
    controlManager->selected_object_rotation(R);
  }

  //----------------------------
}

//Keyboard function
void GUI_control::control_keyboard_oneAction(){
  ImGuiIO io = ImGui::GetIO();
  //----------------------------

  for(int i=0; i<IM_ARRAYSIZE(io.KeysDown); i++){
    if(ImGui::IsKeyPressed(ImGuiKey_Escape)){
      GLFWwindow* window = dimManager->get_window();
      glfwSetWindowShouldClose(window, true);
    }

    //Tab key
    if(ImGui::IsKeyPressed(ImGuiKey_Tab)){
      controlManager->selected_object_next();
      break;
    }

    //Suppr key - Delete selected
    if(ImGui::IsKeyPressed(ImGuiKey_Delete)){
      controlManager->selected_object_deletion();
      break;
    }

    //R key - Reset
    if(ImGui::IsKeyPressed(ImGuiKey_R)){
      //node->reset();
      break;
    }

    /*


    //Fin key - Delete all
    if (ImGui::IsKeyPressed(269)){
      sceneManager->remove_collection_all();
      break;
    }

    //H key - Heatmap
    if (ImGui::IsKeyPressed(72)){
      heatmapManager->make_col_heatmap(collection);
      break;
    }

    //C key - Centering
    if (ImGui::IsKeyPressed(67)){
      this->key_c();
      break;
    }

    //Enter - Validation
    if(ImGui::IsKeyPressed(257)){
      selectionManager->validate();
      break;
    }

    //N key - Save all & remove all & load new
    if(ImGui::IsKeyPressed(78)){
      //pathManager->saving_allCloud();
      //sceneManager->remove_collection_all();
    }

    //o key - Open options
    if(ImGui::IsKeyPressed(79)){
      modal_tab.show_loading = !modal_tab.show_loading;
      break;
    }

    //space key - Start / Pause player
    if(ImGui::IsKeyPressed(32)){
      GUI_Player* gui_player = node_gui->get_gui_player();
      gui_player->player_pause();
      break;
    }*/
  }

  //----------------------------
}
void GUI_control::control_keyboard_camMove(){
  ImGuiIO io = ImGui::GetIO();
  //----------------------------

  for(int i=0; i<IM_ARRAYSIZE(io.KeysDown); i++){
    if(io.MouseDown[1]){

      //Shift speed up
      bool is_fast = false;
      if(io.KeysDown[340]){
        is_fast = true;
      }

      //Z key or Up key
      if(io.KeysDown[571] || io.KeysDown[515]){
        cameraManager->control("up", is_fast);
      }

      //S key or Down key
      if(io.KeysDown[564] || io.KeysDown[516]){
        cameraManager->control("down", is_fast);
      }

      //Q key or Left key
      if(io.KeysDown[562] || io.KeysDown[513]){
        cameraManager->control("left", is_fast);
      }

      //D key or Left key
      if(io.KeysDown[549] || io.KeysDown[514]){
        cameraManager->control("right", is_fast);
      }
    }
  }

  //---------------------------
}
void GUI_control::control_keyboard_translation(){
  ImGuiIO io = ImGui::GetIO();
  //----------------------------

  for (int i = 0; i < IM_ARRAYSIZE(io.KeysDown); i++){
    if(!io.MouseDown[1]){
      float transCoef = 0.01;

      //Shift speed up
      if(io.KeysDown[340]){
        //transCoef = cloud_trans_speed * 5;
      }

      // Z key
      if(io.KeysDown[571]){
        vec3 translation = vec3(transCoef, 0, 0);
        controlManager->selected_object_translation(translation);
        break;
      }
      // S key
      if(io.KeysDown[564]){
        vec3 translation = vec3(-transCoef, 0, 0);
        controlManager->selected_object_translation(translation);
        break;
      }
      // D key
      if(io.KeysDown[549]){
        vec3 translation = vec3(0, transCoef, 0);
        controlManager->selected_object_translation(translation);
        break;
      }
      // Q key
      if(io.KeysDown[562]){
        vec3 translation = vec3(0, -transCoef, 0);
        controlManager->selected_object_translation(translation);
        break;
      }
      // A key
      if(io.KeysDown[546]){
        vec3 translation = vec3(0, 0, transCoef);
        controlManager->selected_object_translation(translation);
        break;
      }
      // E key
      if(io.KeysDown[550]){
        vec3 translation = vec3(0, 0, -transCoef);
        controlManager->selected_object_translation(translation);
        break;
      }
      /*
      // 7 key
      if(io.KeysDown[327]){
        float r = cloud_rotat_degree*M_PI/180;
        vec3 rotation = vec3(0,0,r);
        this->key_rotation(rotation);
        break;
      }
      // 9 key
      if(io.KeysDown[329]){
        float r = cloud_rotat_degree*M_PI/180;
        vec3 rotation = vec3(0,0,-r);
        this->key_rotation(rotation);
        break;
      }*/

      //transCoef = cloud_trans_speed;
    }
  }

  //----------------------------
}
