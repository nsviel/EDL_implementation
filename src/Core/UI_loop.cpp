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
void UI_loop::loop_end(){
  //---------------------------

  ImGui::Render();
  this->draw_data = ImGui::GetDrawData();

  //---------------------------
}
void UI_loop::loop_draw(VkCommandBuffer command){
  //---------------------------

  ImGui_ImplVulkan_RenderDrawData(draw_data, command);

  //---------------------------
}
