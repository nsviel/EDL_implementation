#include "GUI_style.h"

#include "image/IconsFontAwesome5.h"


//Constructor / Destructor
GUI_style::GUI_style(Node_gui* node_gui){
  //---------------------------



  //---------------------------
}
GUI_style::~GUI_style(){}

//Main function
void GUI_style::gui_style(){
  //---------------------------

  this->style_window();
  this->style_widget();

  //---------------------------
}

//Subfunction
void GUI_style::style_window(){
  ImGuiStyle& style = ImGui::GetStyle();
  ImGuiIO& io = ImGui::GetIO();
  //---------------------------

  //Formatting -> rounding
  style.WindowRounding = 0.0f;
  style.TabRounding = 0.0f;
  style.GrabRounding = 0.0f;
  style.ScrollbarRounding = 0.0f;
  style.ChildRounding = 0.0f;
  style.FrameRounding = 0.0f;
  style.PopupRounding = 0.0f;

  //Formatting -> size
  style.FrameBorderSize = 0.0f;
  style.FrameBorderSize = 1.0f;
  style.WindowBorderSize = 0.0f;

  //Colors
  ImGui::PushStyleColor(ImGuiCol_Header, IM_COL32(76, 76, 76, 255));
  ImGui::PushStyleColor(ImGuiCol_Tab, IM_COL32(117, 117, 117, 220));
  ImGui::PushStyleColor(ImGuiCol_Border, IM_COL32(0, 0, 0, 255));
  ImGui::PushStyleColor(ImGuiCol_MenuBarBg, IM_COL32(0, 0, 0, 255));
  ImGui::PushStyleColor(ImGuiCol_ResizeGrip, IM_COL32(15, 15, 15, 255));
  ImGui::PushStyleColor(ImGuiCol_WindowBg, IM_COL32(50, 50, 50, 255));
  ImGui::PushStyleColor(ImGuiCol_PopupBg, IM_COL32(0, 0, 0, 255));
  ImGui::PushStyleColor(ImGuiCol_Separator, IM_COL32(165, 165, 165, 255));

  //IO parameters
  io.ConfigWindowsResizeFromEdges = true;

  //---------------------------
}
void GUI_style::style_widget(){
  ImGuiStyle& style = ImGui::GetStyle();
  ImGuiIO& io = ImGui::GetIO();
  //---------------------------

  //Widget
  ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(120, 120, 120, 255));
  ImGui::PushStyleColor(ImGuiCol_CheckMark, IM_COL32(0, 0, 0, 255));

  //Widget frame
  ImGui::PushStyleColor(ImGuiCol_FrameBg, IM_COL32(120, 120, 120, 255));
  ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, IM_COL32(120, 120, 120, 255));
  ImGui::PushStyleColor(ImGuiCol_FrameBgActive, IM_COL32(120, 120, 120, 255));

  //Slider
  ImGui::PushStyleColor(ImGuiCol_SliderGrab, IM_COL32(0, 0, 0, 255));
  ImGui::PushStyleColor(ImGuiCol_SliderGrabActive, IM_COL32(0, 0, 0, 255));

  //Table
  ImGui::PushStyleColor(ImGuiCol_TableBorderStrong, IM_COL32(0, 0, 0, 255));
  ImGui::PushStyleColor(ImGuiCol_TableRowBg, IM_COL32(35, 35, 35, 255));
  ImGui::PushStyleColor(ImGuiCol_TableRowBgAlt, IM_COL32(25, 25, 25, 255));

  //---------------------------
}
