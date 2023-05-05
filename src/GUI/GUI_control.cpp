#include "GUI_control.h"

#include "../Engine/Node_engine.h"
#include "../Engine/Dimension/Dimension.h"
#include "../Engine/Core/Control.h"
#include "../Engine/Camera/Camera.h"


//Constructor / Destructor
GUI_control::GUI_control(Node_engine* node_engine){
  //---------------------------

  this->node_engine = node_engine;
  this->dimManager = node_engine->get_dimManager();
  this->cameraManager = node_engine->get_cameraManager();
  this->controlManager = node_engine->get_controlManager();

  //---------------------------
}
GUI_control::~GUI_control(){}

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
  Tab* tab_rendering = dimManager->get_tab("rendering");
  ImGuiIO io = ImGui::GetIO();
  Cam* camera = cameraManager->get_camera();
  //----------------------------

  //Right click - Camera movement
  static vec2 cursorPos;
  if(ImGui::IsMouseClicked(1) && !io.WantCaptureMouse){
    cursorPos = dimManager->get_mouse_pose();
    dimManager->set_mouse_visibility(false);
    dimManager->set_mouse_pose(tab_rendering->center);
    camera->cam_move = true;
  }
  //Release - back to normal
  if(ImGui::IsMouseReleased(1) && camera->cam_move){
    dimManager->set_mouse_visibility(true);
    dimManager->set_mouse_pose(cursorPos);
    camera->cam_move = false;
  }

  //---------------------------
}
void GUI_control::control_mouse_wheel(){
  static int wheelMode = 0;
  ImGuiIO io = ImGui::GetIO();
  //----------------------------

  //Wheel + right clicked - Camera zoom
  if(io.MouseWheel && io.MouseDownDuration[1] >= 0.0f && !io.WantCaptureMouse){
    cameraManager->compute_zoom(io.MouseWheel);
  }
  /*
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
*/
  //----------------------------
}

//Keyboard function
void GUI_control::control_keyboard_oneAction(){
  ImGuiIO io = ImGui::GetIO();
  //----------------------------

  for(int i=0; i<IM_ARRAYSIZE(io.KeysDown); i++){
    if(ImGui::IsKeyPressed(ImGuiKey_Escape)){
      controlManager->exit();
    }
    /*
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
    }*/
  }

  //----------------------------
}
void GUI_control::control_keyboard_camMove(){
  ImGuiIO io = ImGui::GetIO();
  //----------------------------

  for(int i=0; i<IM_ARRAYSIZE(io.KeysDown); i++){
    if(io.MouseDown[1] && !io.WantCaptureMouse){

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
