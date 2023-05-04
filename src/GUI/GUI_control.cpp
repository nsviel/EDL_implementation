#include "GUI_control.h"

#include "../Engine/Node_engine.h"
#include "../Engine/Dimension/Dimension.h"


//Constructor / Destructor
GUI_control::GUI_control(Node_engine* node_engine){
  //---------------------------

  this->node_engine = node_engine;
  this->dimManager = node_engine->get_dimManager();

  //---------------------------
}
GUI_control::~GUI_control(){}
/*
//Main function
void GUI_control::make_control(){
  //---------------------------

  this->control_mouse();
  this->control_mouse_wheel();
  this->control_keyboard_oneAction();
  this->control_keyboard_camMove();

  //---------------------------
}

//Mouse function
void GUI_control::control_mouse(){
  ImGuiIO io = ImGui::GetIO();
  GLFWwindow* window = dimManager->get_window();
  Viewport_obj* view = cameraManager->get_current_viewport();
  //----------------------------

  //Right click - Camera movement
  static vec2 cursorPos;
  if(ImGui::IsMouseClicked(1) && !io.WantCaptureMouse){
    //Save cursor position
    cursorPos = dimManager->get_mouse_pose();

    //Hide cursor
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

    //Set cursor to screen middle
    vec2 glMiddle = dimManager->get_gl_middle();
    glfwSetCursorPos(window, glMiddle.x, glMiddle.y);

    //Enable camera movement
    view->cam_move = true;
  }
  //Right click release
  if(ImGui::IsMouseReleased(1) && cameraManager->is_cameraMovON()){
    //Restaure cursor position
    dimManager->set_mouse_pose(cursorPos);

    //Disable camera movement
    view->cam_move = false;
  }
  if(io.MouseDown[1] && !io.WantCaptureMouse){
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
  }

  //---------------------------
}
void GUI_control::control_mouse_wheel(){
  Collection* collection = sceneManager->get_selected_collection();
  static int wheelMode = 0;
  ImGuiIO io = ImGui::GetIO();
  //----------------------------

  //Wheel + right clicked - Camera zoom
  if(io.MouseWheel && io.MouseDownDuration[1] >= 0.0f && !io.WantCaptureMouse){
    cameraManager->compute_zoom_position(io.MouseWheel);
  }

  //Wheel click - Change mouse wheel mode
  if(ImGui::IsMouseClicked(2) && !io.WantCaptureMouse){
    wheelMode++;
    if(wheelMode >= 3) wheelMode = 0;
  }

  //Wheel actions
  if(io.MouseWheel && io.MouseDownDuration[1] == -1 && !io.WantCaptureMouse){
    //Get wheel direction
    string direction;
    if(io.MouseWheel > 0){
      direction = "up";
    }else{
      direction = "down";
    }

    //Subset rotation
    if(sceneManager->get_is_list_empty() == false){
      if(collection->nb_obj == 1 && collection->is_onthefly == false){
        float radian = cloud_rotat_degree*M_PI/180;
        vec3 R;
        if(wheelMode == 0){
          R = vec3(0, 0, radian);
        }
        else if(wheelMode == 1){
          R = vec3(0, radian, 0);
        }
        else if(wheelMode == 2){
          R = vec3(radian, 0, 0);
        }

        poseManager->compute_COM(collection);
        transformManager->make_rotation(collection, R, direction);
        sceneManager->update_buffer_location(collection->selected_obj);
        sceneManager->update_glyph(collection);
      }
      //Subset selection
      else if(collection->nb_obj > 1 || collection->is_onthefly){
        playerManager->compute_wheel_selection(direction);
      }
    }
  }

  //----------------------------
}

//Keyboard function
void GUI_control::control_keyboard_oneAction(){
  Collection* collection = sceneManager->get_selected_collection();
  ImGuiIO io = ImGui::GetIO();
  GLFWwindow* window = glfwGetCurrentContext();
  //----------------------------

  for (int i = 0; i < IM_ARRAYSIZE(io.KeysDown); i++){
    //Esc key
    if(ImGui::IsKeyPressed(256)){
      node_gui->exit();
    }

    //Tab key
    if (ImGui::IsKeyPressed(258)){
      bool* highlightON = extractionManager->get_highlightON();
      *highlightON = false;

      //Select the next collection in the list
      graphManager->select_next_collection();
      break;
    }

    //Suppr key - Delete selected
    if (ImGui::IsKeyPressed(261)){
      this->key_suppr();
      break;
    }

    //Fin key - Delete all
    if (ImGui::IsKeyPressed(269)){
      sceneManager->remove_collection_all();
      break;
    }

    //R key - Reset
    if (ImGui::IsKeyPressed(82) && !io.WantCaptureMouse){
      node_gui->reset();
      break;
    }

    //H key - Heatmap
    if (ImGui::IsKeyPressed(72) && !io.WantCaptureMouse){
      heatmapManager->make_col_heatmap(collection);
      break;
    }

    //C key - Centering
    if (ImGui::IsKeyPressed(67) && !io.WantCaptureMouse){
      this->key_c();
      break;
    }

    //Enter - Validation
    if(ImGui::IsKeyPressed(257) && !io.WantCaptureMouse){
      selectionManager->validate();
      break;
    }

    //N key - Save all & remove all & load new
    if(ImGui::IsKeyPressed(78) && !io.WantCaptureMouse){
      //pathManager->saving_allCloud();
      //sceneManager->remove_collection_all();
    }

    //o key - Open options
    if(ImGui::IsKeyPressed(79) && !io.WantCaptureMouse){
      modal_tab.show_loading = !modal_tab.show_loading;
      break;
    }

    //space key - Start / Pause player
    if(ImGui::IsKeyPressed(32) && !io.WantCaptureMouse){
      GUI_Player* gui_player = node_gui->get_gui_player();
      gui_player->player_pause();
      break;
    }
  }

  //----------------------------
}
void GUI_control::control_keyboard_camMove(){
  ImGuiIO io = ImGui::GetIO();
  Viewport_obj* view = cameraManager->get_current_viewport();
  //----------------------------

  if(view->cam_move){
    float delta = 0.00016;
    float cam_speed = view->speed_move * delta;
    float cam_speed_fast = view->speed_move * delta * 5;

    for (int i = 0; i < IM_ARRAYSIZE(io.KeysDown); i++){
      if(io.MouseDown[1] && !io.WantCaptureMouse){

        //Shift speed up
        if(io.KeysDown[340]){
          cam_speed = cam_speed_fast;
        }

        //Z key or Up key
        if(io.KeysDown[87] || io.KeysDown[265]){
          if(view->view == "top"){
            view->cam_P += view->cam_U * cam_speed;
          }else{
            vec3 old = view->cam_P;
            view->cam_P += view->cam_F * cam_speed;
          }
        }

        //S key or Down key
        if(io.KeysDown[83] || io.KeysDown[264]){
          if(view->view == "top"){
            view->cam_P -= view->cam_U * cam_speed;
          }else{
            view->cam_P -= view->cam_F * cam_speed;
          }
        }

        //Q key or Right key
        if(io.KeysDown[65] || io.KeysDown[263]){
          if(view->mode == "default"){
            view->cam_P -= view->cam_R * cam_speed;
          }else if(view->mode == "arcball"){
            vec2 angle =vec2(-cam_speed/10, 0);
            cameraManager->arcball_viewport_angle(angle);
            cameraManager->compute_cam_arcball();
          }
        }

        //D key or Left key
        if(io.KeysDown[68] || io.KeysDown[262]){
          if(view->mode == "default"){
            view->cam_P += view->cam_R * cam_speed;
          }else if(view->mode == "arcball"){
            vec2 angle =vec2(cam_speed/10, 0);
            cameraManager->arcball_viewport_angle(angle);
            cameraManager->compute_cam_arcball();
          }
        }
      }
    }
  }

  //---------------------------
}
*/
