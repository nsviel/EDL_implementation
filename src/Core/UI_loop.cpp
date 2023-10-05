#include "UI_loop.h"


//Constructor / Destructor
UI_loop::UI_loop(){
  //---------------------------


  //---------------------------
}
UI_loop::~UI_loop(){}

//Main function
void UI_loop::loop_start(){
  //---------------------------

  ImGui_ImplVulkan_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();

  //---------------------------
}
