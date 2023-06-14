#include "GUI_option.h"

#include "../Node_gui.h"

#include "../../Engine/Node_engine.h"
#include "../../Engine/Param_engine.h"
#include "../../Engine/Vulkan/VK_engine.h"
#include "../../Engine/Vulkan/VK_param.h"


//Constructor / Destructor
GUI_option::GUI_option(Node_gui* node_gui){
  //---------------------------

  this->node_gui = node_gui;
  this->node_engine = node_gui->get_node_engine();
  this->vk_engine = node_engine->get_vk_engine();
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

  static int font_selected = 0;
  ImGui::SetNextItemWidth(150);
  if(ImGui::Combo("Font size", &font_selected, "13\0 12\0")){
    ImFont* font = io.Fonts->Fonts[font_selected];
    io.FontDefault = font;
  }

  //---------------------------
  ImGui::Separator();
}
void GUI_option::option_color(){
  if(ImGui::CollapsingHeader("Colors")){
    Param_engine* param_engine = node_engine->get_param_engine();
    //---------------------------

    //Background color
    vec4* screen_color = &param_engine->background_color;
    ImGui::SetNextItemWidth(width);
    ImGui::ColorEdit4("Background", (float*)screen_color);

    //---------------------------
    ImGui::Separator();
  }
}
void GUI_option::option_fps(){
  Param_engine* param_engine = node_engine->get_param_engine();
  //---------------------------

  //FPS max value
  ImGui::SetNextItemWidth(150);
  ImGui::SliderInt("FPS max", &param_engine->max_fps, 10, 1000);

  //---------------------------
}
void GUI_option::option_line_width(){
  Object* object = new Object();
  ImGuiStyle& style = ImGui::GetStyle();
  //---------------------------

  //Point size
  ImGui::Columns(2);
  ImGui::AlignTextToFramePadding();
  ImGui::Text("Line width ");
  ImGui::NextColumn();
  ImGui::PushButtonRepeat(true);
  static int line_width = 1;
  if(object != nullptr){
    line_width = object->draw_line_width;
  }
  if (ImGui::ArrowButton("##left", ImGuiDir_Left) && object != nullptr){
    object->draw_line_width--;

    if(object->draw_line_width <= 1){
      object->draw_line_width = 1;
    }
  }
  ImGui::SameLine(0.0f, style.ItemInnerSpacing.x);
  if (ImGui::ArrowButton("##right", ImGuiDir_Right) && object != nullptr){
    object->draw_line_width++;

    line_width = object->draw_line_width;
  }
  ImGui::PopButtonRepeat();
  ImGui::SameLine();
  ImGui::Text("%d", line_width);
  ImGui::NextColumn();

  //---------------------------
}
