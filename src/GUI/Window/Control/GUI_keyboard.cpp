#include "GUI_keyboard.h"

#include <GUI.h>
#include <Engine.h>
#include <Window/Window.h>
#include <Data/Data_node.h>
#include <Specific/Function/fct_math.h>
#include <Render/Render_node.h>
#include <Render/Render_param.h>
#include <Data/Scene/Scene.h>
#include <Data/Data_node.h>
#include <Camera/Camera.h>
#include <Operation/Transformation/Transformation.h>


//Constructor / Destructor
GUI_keyboard::GUI_keyboard(GUI* gui){
  //---------------------------

  Data_node* data_node = gui->get_data_node();
  Render_node* render_node = gui->get_node_render();
  this->window = render_node->get_window();
  this->cameraManager = render_node->get_cameraManager();
  this->sceneManager = data_node->get_sceneManager();
  this->transformManager = new Transformation();

  //---------------------------
}
GUI_keyboard::~GUI_keyboard(){}

//Main function
void GUI_keyboard::run_control(){
  //---------------------------

  this->control_keyboard_oneAction();
  this->control_keyboard_camMove();
  this->control_keyboard_translation();

  //---------------------------
}

//Keyboard function
void GUI_keyboard::control_keyboard_oneAction(){
  ImGuiIO io = ImGui::GetIO();
  //----------------------------

  for(int i=0; i<IM_ARRAYSIZE(io.KeysDown); i++){
    if(ImGui::IsKeyPressed(ImGuiKey_Escape)){
      window->close_window();
    }

    //Tab key
    if(ImGui::IsKeyPressed(ImGuiKey_Tab)){
      sceneManager->selected_object_next();
      break;
    }

    //Suppr key - Delete selected
    if(ImGui::IsKeyPressed(ImGuiKey_Delete)){
      Set* set = sceneManager->get_set_scene();
      Object* object = set->selected_obj;
      sceneManager->selected_object_next();
      sceneManager->delete_scene_object(object);
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
      GUI_Player* gui_player = gui->get_gui_player();
      gui_player->player_pause();
      break;
    }*/
  }

  //----------------------------
}
void GUI_keyboard::control_keyboard_camMove(){
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
void GUI_keyboard::control_keyboard_translation(){
  Set* set = sceneManager->get_set_scene();
  ImGuiIO io = ImGui::GetIO();
  //----------------------------

  for (int i = 0; i < IM_ARRAYSIZE(io.KeysDown); i++){
    if(!io.MouseDown[1]){
      float transCoef = 0.01;

      //Shift speed up
      if(io.KeysDown[340]){
        //transCoef = cloud_trans_speed * 5;
      }


      //---------------------------





      // Z key
      if(io.KeysDown[571]){
        vec3 translation = vec3(transCoef, 0, 0);
        transformManager->make_translation(set->selected_obj, translation);
        break;
      }
      // S key
      if(io.KeysDown[564]){
        vec3 translation = vec3(-transCoef, 0, 0);
        transformManager->make_translation(set->selected_obj, translation);
        break;
      }
      // D key
      if(io.KeysDown[549]){
        vec3 translation = vec3(0, transCoef, 0);
        transformManager->make_translation(set->selected_obj, translation);
        break;
      }
      // Q key
      if(io.KeysDown[562]){
        vec3 translation = vec3(0, -transCoef, 0);
        transformManager->make_translation(set->selected_obj, translation);
        break;
      }
      // A key
      if(io.KeysDown[546]){
        vec3 translation = vec3(0, 0, transCoef);
        transformManager->make_translation(set->selected_obj, translation);
        break;
      }
      // E key
      if(io.KeysDown[550]){
        vec3 translation = vec3(0, 0, -transCoef);
        transformManager->make_translation(set->selected_obj, translation);
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
