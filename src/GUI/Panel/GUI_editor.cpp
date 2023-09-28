#include "GUI_editor.h"
#include "../Node_gui.h"

#include "../../../extern/imgui/editor/editor_memory.h"


//Constructor / Destructor
GUI_editor::GUI_editor(Node_gui* node_gui){
  //---------------------------

  this->editor = new TextEditor();
  editor->SetText("Hello there !");
  this->load_file("/home/aeter/Desktop/Dev/Nephos/CMakeLists.txt");

  //---------------------------
}
GUI_editor::~GUI_editor(){}

//Main function
void GUI_editor::design_editor_text(){
  //---------------------------

  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
  ImGui::SetNextWindowSizeConstraints(ImVec2(100, 100), ImVec2(500, 500));
  ImGui::Begin("Text editor");
  editor->Render("hello");
  ImGui::End();
  ImGui::PopStyleVar();

  //---------------------------
}

//Subfunction
void GUI_editor::load_file(string path){
  //---------------------------

  string item_name;
  ifstream nameFileout;
  nameFileout.open(path);
  string line;
  string file = "";
  while(std::getline(nameFileout, line))
  {
    file = file + "\n" + line;
  }

  editor->SetText(file);


  //---------------------------
}
void GUI_editor::design_editor_memory(){
  //---------------------------

  static MemoryEditor mem_edit;
  static char data[0x10000];
  size_t data_size = 0x10000;
  mem_edit.DrawWindow("Memory Editor", data, data_size);

  //---------------------------
}
