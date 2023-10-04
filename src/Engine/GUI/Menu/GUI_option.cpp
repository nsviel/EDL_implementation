#include "GUI_option.h"

#include "../Node_gui.h"

#include "../../Core/Core_node.h"
#include "../../Core/Core_param.h"
#include "../../Core/Vulkan/VK_engine.h"
#include "../../Core/Vulkan/VK_param.h"


//Constructor / Destructor
GUI_option::GUI_option(Node_gui* node_gui){
  //---------------------------

  this->node_gui = node_gui;
  this->core_node = node_gui->get_core_node();
  this->vk_engine = core_node->get_vk_engine();
  this->vk_param = vk_engine->get_vk_param();

  this->width = 150;

  //---------------------------
}
GUI_option::~GUI_option(){}

//Main function
void GUI_option::design_option(){
  //---------------------------

  this->option_font();
  this->option_color();
  this->option_fps();

  //---------------------------
}

//Subfunctions
void GUI_option::option_font(){
  ImGuiIO& io = ImGui::GetIO();
  //---------------------------

  ImFont* font_current = ImGui::GetFont();
  if (ImGui::BeginCombo("Font", font_current->GetDebugName())){
    for (ImFont* font : io.Fonts->Fonts){
      ImGui::PushID((void*)font);
      if (ImGui::Selectable(font->GetDebugName(), font == font_current)){
        io.FontDefault = font;
      }
      ImGui::PopID();
    }
    ImGui::EndCombo();
  }

  //---------------------------
  ImGui::Separator();
}
void GUI_option::option_color(){
  if(ImGui::CollapsingHeader("Colors")){
    Core_param* core_param = core_node->get_core_param();
    //---------------------------

    //Background color
    vec4* screen_color = &core_param->background_color;
    ImGui::SetNextItemWidth(width);
    ImGui::ColorEdit4("Background", (float*)screen_color);

    //---------------------------
    ImGui::Separator();
  }
}
void GUI_option::option_fps(){
  Core_param* core_param = core_node->get_core_param();
  //---------------------------

  //FPS max value
  ImGui::SetNextItemWidth(150);
  ImGui::SliderInt("FPS max", &core_param->max_fps, 10, 1000);

  //---------------------------
}
