#include "GUI_editor.h"
#include "../Node_gui.h"


//Constructor / Destructor
GUI_editor::GUI_editor(Node_gui* node_gui){
  //---------------------------

  this->editor = new TextEditor();
  editor->SetText("hello\n\nkeiuhfezkf\njzgefjez");

  //---------------------------
}
GUI_editor::~GUI_editor(){}

//Main function
void GUI_editor::design_panel(){
  //---------------------------

  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
  ImGui::SetNextWindowSizeConstraints(ImVec2(100, 100), ImVec2(500, 500));
  ImGui::Begin("Text editor");
  editor->Render("hello");
  ImGui::End();
  ImGui::PopStyleVar();

  //---------------------------
}
